```markdown
# miniRT - My First RayTracer with MiniLibX

**Version:** 8.5

**Summary:**
This project is an introduction to the beautiful world of Raytracing. Once completed, you will be able to render simple computer-generated images, and you will never be afraid of implementing mathematical formulas again.

---

## 📋 Table of Contents

| Section                                | Page |
|----------------------------------------|------|
| I. Introduction                        | 2    |
| II. Common Instructions                | 3    |
| III. Mandatory Part - miniRT           | 5    |
| IV. Bonus Part                         | 10   |
| V. Examples                            | 12   |
| VI. Submission and Peer-Evaluation     | 17   |

---

## 🧠 I. Introduction

When it comes to rendering three-dimensional computer-generated images, there are two possible approaches:

- **Rasterization**: Used by almost all graphics engines because of its efficiency.
- **Ray Tracing**: Developed originally in 1968 and improved since; more computationally expensive but produces a much higher degree of visual realism.

> **Figure I.1:** The pictures above are rendered with the ray tracing technique. Impressive, isn’t it?

**Goal of miniRT:**
- Build a simple Ray Tracer (`miniRT`) in C, using the MiniLibX library.
- Master the basics of mathematical/physical formulas required for CGI.
- Produce simple yet impressive computer-generated images.

---

## ⚙️ II. Common Instructions

- **Language**: C
- **Norm Compliance**: All code (mandatory and bonus) must adhere to the Norm. Any norm error → **0 points**.
- **Stability**: Functions must not crash (segfault, bus error, double free, etc.). Any crash → **non-functional** → **0 points**.
- **Memory Management**: Free all heap-allocated memory. **Memory leaks are not tolerated**.
- **Makefile Requirements**:
  - Compile with `cc -Wall -Wextra -Werror`.
  - Do NOT perform unnecessary relinking.
  - Must include rules: `$(NAME)`, `all`, `clean`, `fclean`, `re`, and `bonus`.
  - **Bonus** rule compiles additional `_bonus.c/h` files.
- **Libft**:
  - If used, copy libft sources and its Makefile into a `libft/` directory.
  - Your project’s Makefile must first build `libft`, then your program.
- **Testing**: Encouraged to write test programs (not graded) for your own and peers’ code; you may use these tests during the defense.
- **Submission**: Push your work to the assigned Git repository. Only repository content is graded.
  - If Deepthought grading is used, it runs after peer evaluations.
  - If an error occurs anywhere during Deepthought grading, evaluation stops.

---

## 🎯 III. Mandatory Part - miniRT

**Program Name:** `miniRT`

**Deliverables:**
- All your source files.
- `Makefile` with required rules.

**Execution:**
```
./miniRT <scene_file.rt>
```

**Allowed External Functions:**
```
open, close, read, write,
printf, malloc, free, perror,
strerror, exit,
(math.h functions - link with -lm),
MiniLibX library functions
```

**Libft:** Authorized (see Common Instructions).

### 1. Description
Generate images using the ray tracing protocol. Each image represents a scene defined by:
- **Geometric Objects**: plane, sphere, cylinder.
- **Camera Viewpoint**.
- **Lighting System**.

**Constraints:**
- Use MiniLibX (system or source version).
- Window management must remain fluid (resizing, focus, minimization).
- Implement at least three geometric primitives:
  - **Plane**
  - **Sphere**
  - **Cylinder**
- Handle intersections and object interiors correctly.
- Allow resizing of object properties (diameter, width, height).
- Support translation & rotation for objects, lights, and cameras (except spheres and lights cannot rotate).
- **Lighting Model**:
  - Ambient lighting (no object fully dark).
  - Diffuse lighting.
  - Spot brightness and hard shadows (if implemented; ambient & diffuse are mandatory).
- **Controls**:
  - **ESC** key: exit cleanly.
  - Window close (red cross): exit cleanly.
- Use MiniLibX images to render when possible.

### 2. Scene File Format (`.rt`)
- File extension must be `.rt`.
- Elements separated by blank lines or spaces; order is arbitrary.
- Capital-letter elements (`A`, `C`, `L`) declared only once.

#### Element Definitions

1. **Ambient Lighting**
   ```
   A <ratio> <R,G,B>
   ```
   - `A`: ambient identifier
   - `ratio` ∈ [0.0,1.0]
   - `R,G,B` ∈ [0–255]

2. **Camera**
   ```
   C <X,Y,Z> <dirX,dirY,dirZ> <FOV>
   ```
   - `C`: camera identifier
   - `<X,Y,Z>`: viewpoint coordinates
   - `<dirX,dirY,dirZ>`: orientation vector (normalized)
   - `FOV`: horizontal field of view in degrees ∈ [0,180]

3. **Light**
   ```
   L <X,Y,Z> <brightness> <R,G,B>
   ```
   - `L`: light identifier
   - `<X,Y,Z>`: light position
   - `brightness` ∈ [0.0,1.0]
   - `R,G,B` ∈ [0–255] (color unused in mandatory part)

4. **Sphere**
   ```
   sp <centerX,centerY,centerZ> <diameter> <R,G,B>
   ```
   - `sp`: sphere identifier
   - `<centerX,centerY,centerZ>`: center coordinates
   - `diameter`: sphere diameter
   - `R,G,B`: color

5. **Plane**
   ```
   pl <pointX,pointY,pointZ> <normX,normY,normZ> <R,G,B>
   ```
   - `pl`: plane identifier
   - `<pointX,pointY,pointZ>`: a point on the plane
   - `<normX,normY,normZ>`: normal vector (normalized)
   - `R,G,B`: color

6. **Cylinder**
   ```
   cy <centerX,centerY,centerZ> <axisX,axisY,axisZ> <diameter> <height> <R,G,B>
   ```
   - `cy`: cylinder identifier
   - `<centerX,centerY,centerZ>`: center coordinates
   - `<axisX,axisY,axisZ>`: axis vector (normalized)
   - `diameter`: cylinder diameter
   - `height`: cylinder height
   - `R,G,B`: color

**Error Handling:**
- On any misconfiguration: print to `stdout`:
  ```
  Error
  <your message>
  ```
  and exit.

**Example Minimal Scene**
```plaintext
A 0.2 255,255,255

C -50,0,20 0,0,1 70
L -40,0,30 0.7 255,255,255

pl 0,0,0 0,1,0 255,0,225
sp 0,0,20 20 255,0,0
cy 50,0,20.6 0,0,1 14.2 21.42 10,0,255
```

---

## 💎 IV. Bonus Part

> **Note:** Bonuses are evaluated **only if** the mandatory part is perfect.

**Possible Bonuses:**
- Specular reflection (Phong shading).
- Checkerboard pattern textures.
- Colored & multi-spot lights.
- Additional quadric shapes (cone, paraboloid, hyperboloid).
- Bump map texturing.

You may extend the scene file format for new features. Be prepared to justify changes during defense.

---

## 📸 V. Examples

Figures illustrating various scenes (see PDF):

1. Shiny sphere with one spot light.
2. Cylinder with one spot.
3. Cone, plane, one spot (bonus cone).
4. Mixed objects including two planes.
5. Same scene, different camera angle.
6. Scene with shadows.
7. Multiple spot lights.
8. Multi-spot & checkered sphere with bump map (optional).

---

## 📤 VI. Submission and Peer-Evaluation

- Submit to the **assigned Git repository** only.
- Only files in the repository are graded.
- Ensure correct filenames and structure.
- Peer evaluation occurs first; Deepthought grading follows.
- On Deepthought grading error, evaluation stops.

<!-- End of Subject -->
```

