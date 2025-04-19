# Ray-Object Intersection Guide for MiniRT

## Základní princip sledování paprsku (Ray Tracing)

Ray tracing funguje na principu sledování paprsků světla od kamery skrz pixely do scény. Pro každý pixel musíme zjistit, s jakým objektem se paprsek protne, a pokud se protne s více objekty, vybereme ten nejbližší.

Paprsek (ray) je definován:
- **Počátečním bodem** (origin) - typicky pozice kamery
- **Směrovým vektorem** (direction) - normalizovaný vektor určující směr paprsku

Každý paprsek lze parametricky vyjádřit rovnicí:
```
P(t) = O + t * D
```
kde:
- P(t) je bod na paprsku v parametru t
- O je počáteční bod paprsku (origin)
- D je směrový vektor paprsku (direction)
- t je parametr (pro t > 0 jdeme "dopředu" od kamery)

## 1. Průsečík paprsku s koulí (Sphere)

### Matematický princip

Koule je definována středem C a poloměrem r. Bod P leží na kouli, pokud:
```
|P - C|² = r²
```

Dosadíme-li parametrické vyjádření paprsku:
```
|O + t*D - C|² = r²
```

Po úpravě dostaneme kvadratickou rovnici:
```
a*t² + b*t + c = 0
```
kde:
- a = D·D (dot product směrového vektoru se sebou samým, pro normalizovaný = 1)
- b = 2 * D·(O-C)
- c = (O-C)·(O-C) - r²

### Implementace krok za krokem

1. Vypočteme vektor OC (od středu koule k počátku paprsku):
   ```c
   t_vector oc = vec_sub(ray.origin, sphere.center);
   ```

2. Vypočteme koeficienty kvadratické rovnice:
   ```c
   double a = dot_product(ray.direction, ray.direction);
   double b = 2.0 * dot_product(oc, ray.direction);
   double c = dot_product(oc, oc) - sphere.radius * sphere.radius;
   ```

3. Vypočteme diskriminant:
   ```c
   double delta = b*b - 4*a*c;
   ```
   - Pokud delta < 0: Paprsek neprotíná kouli (žádné řešení)
   - Pokud delta = 0: Paprsek se dotýká koule (jedno řešení)
   - Pokud delta > 0: Paprsek protíná kouli (dvě řešení)

4. Pokud existuje řešení, vypočteme t:
   ```c
   double t0 = (-b - sqrt(delta)) / (2*a);  // první průsečík
   double t1 = (-b + sqrt(delta)) / (2*a);  // druhý průsečík
   ```

5. Vybereme nejmenší platné t (nejbližší průsečík v "dopředném" směru):
   ```c
   double t = INFINITY;
   if (t0 > RAY_T_MIN && t0 < RAY_T_MAX) t = t0;
   if (t1 > RAY_T_MIN && t1 < t && t1 < RAY_T_MAX) t = t1;
   ```

6. Vypočteme bod průsečíku a normálu:
   ```c
   col.point = ray_point(ray, t);
   t_vector n = vec_sub(col.point, sphere.center);
   normalize_vec(&n);
   col.normal = n;
   ```

### Vizualizace

```
    O
     \          Paprsek
      \        /
       \      /
        \    /
         \  /
          \/  Průsečík
           \
            \      Koule
             *-----*
            /|     \
           / |      \
          *--+-------*
             C (střed)
```

## 2. Průsečík paprsku s rovinou (Plane)

### Matematický princip

Rovina je definována bodem P₀ ležícím v rovině a normálovým vektorem n. Bod P leží v rovině, pokud:
```
(P - P₀)·n = 0
```

Dosadíme-li parametrické vyjádření paprsku:
```
(O + t*D - P₀)·n = 0
```

Řešením pro t dostaneme:
```
t = (P₀ - O)·n / (D·n)
```

### Implementace krok za krokem

1. Vypočteme jmenovatel (denominator) - dot product směru paprsku a normály roviny:
   ```c
   double denom = dot_product(ray.direction, plane.normal);
   ```
   - Pokud denom ≈ 0: Paprsek je rovnoběžný s rovinou (žádný průsečík)

2. Vypočteme čitatel (numerator) a hodnotu parametru t:
   ```c
   t_vector P0_O = vec_sub(plane.point, ray.origin);
   double numer = dot_product(P0_O, plane.normal);
   double t = numer / denom;
   ```

3. Zkontrolujeme, zda t je v platném rozsahu:
   ```c
   if (t <= RAY_T_MIN || t >= RAY_T_MAX) return col;
   ```

4. Vypočteme bod průsečíku (normála je již daná vlastností roviny):
   ```c
   col.point = ray_point(ray, t);
   col.normal = plane.normal;
   ```

### Vizualizace

```
               n (normála)
               ↑
               |
               |
    O          |           Rovina
     \         |          /
      \        |         /
       \       |        /
        \      |       /
         \     |      /
          \    |     /
           \   |    /
            \  |   /
             \ |  /
              \| /
               * P₀
              /|\
             / | \
```

## 3. Průsečík paprsku s válcem (Cylinder)

Válec je komplikovanější objekt skládající se ze tří částí:
- Plášť (boční stěna)
- Horní podstava (disk)
- Dolní podstava (disk)

### Matematický princip

Válec je definován středovým bodem C na ose, směrovým vektorem osy a, poloměrem r a výškou h.

1. Pro plášť válce musíme:
   - Najít průsečíky s "nekonečným" válcem
   - Kontrolovat, zda průsečíky leží v rozmezí výšky válce

2. Pro podstavy musíme:
   - Najít průsečíky s rovinami podstav
   - Kontrolovat, zda průsečíky leží uvnitř kruhu podstavy

### Implementace pláště válce

1. Definujeme pomocné vektory a hodnoty:
   ```c
   t_vector oc = vec_sub(ray.origin, cyl.center);
   double r = cyl.diameter * 0.5;
   t_vector axis = cyl.axis;
   ```

2. Vypočteme koeficienty kvadratické rovnice (složitější než u koule):
   ```c
   double dd_a = dot_product(ray.direction, axis);
   double oc_a = dot_product(oc, axis);
   double a = dot_product(ray.direction, ray.direction) - dd_a*dd_a;
   double b = 2*(dot_product(ray.direction, oc) - dd_a*oc_a);
   double c = dot_product(oc, oc) - oc_a*oc_a - r*r;
   ```

3. Řešíme kvadratickou rovnici a kontrolujeme, zda průsečíky leží v rozmezí výšky válce:
   ```c
   // Pro každý průsečík (t0, t1)
   t_vector p = ray_point(ray, t);
   double m = dot_product(vec_sub(p, cyl.center), axis);
   if (m >= 0 && m <= cyl.height) {
       // Máme platný průsečík s pláštěm
   }
   ```

### Implementace podstav válce

Pro podstavy válce používáme funkci `intersect_cylinder_caps`, která najde průsečíky s rovinami podstav a ověří, zda jsou uvnitř kruhu.

### Určení normály

Normála závisí na tom, s jakou částí válce se paprsek protnul:
- Pro plášť: Normála směřuje od osy válce k bodu průsečíku
- Pro dolní podstavu: Normála je opačný vektor osy
- Pro horní podstavu: Normála je stejná jako vektor osy

```c
// Pro plášť
double m = dot_product(vec_sub(col.point, cyl.center), axis);
t_vector on_axis = vec_add(cyl.center, vec_mult_scalar(axis, m));
t_vector n = vec_sub(col.point, on_axis);
normalize_vec(&n);
col.normal = n;

// Pro podstavy
if (hit_type == HIT_BOT_CAP)
    col.normal = vec_mult_scalar(axis, -1.0);
else // TOP_CAP
    col.normal = axis;
```

### Vizualizace

```
            *-------*  ← Horní podstava
           /|       |\
          / |       | \
         /  |       |  \  ← Plášť
        /   |       |   \
       /    |       |    \
      *-----+-------+-----*  ← Dolní podstava
            |       |
            |   a   |  ← Osa válce
            |       |
            C       ← Střed válce
```

## Obecná implementace průsečíků

Každá funkce průsečíku vrací strukturu `t_collision`, která obsahuje:
- `hit` - zda došlo k průsečíku (true/false)
- `t` - parametr t průsečíku (vzdálenost)
- `point` - souřadnice bodu průsečíku
- `normal` - normálový vektor v bodě průsečíku
- `color` - barva objektu v bodě průsečíku

Inicializace struktury:
```c
static t_collision init_collision(void)
{
    t_collision col;
    col.hit    = false;
    col.t      = INFINITY;
    col.point  = (t_vector){0,0,0};
    col.normal = (t_vector){0,0,0};
    col.color  = (t_rgb){0,0,0};
    return col;
}
```

## Shrnutí

1. **Koule**: Řešíme kvadratickou rovnici pro průsečík paprsku s koulí.
2. **Rovina**: Využíváme lineární rovnici pro průsečík paprsku s rovinou.
3. **Válec**: Kombinujeme kvadratické řešení pro plášť a lineární řešení pro podstavy.

Pro všechny objekty:
- Kontrolujeme platný rozsah parametru t (RAY_T_MIN < t < RAY_T_MAX)
- Vypočítáváme normálu v bodě průsečíku
- Přiřazujeme barvu z vlastností objektu
