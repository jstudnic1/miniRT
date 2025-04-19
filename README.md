## Parser Changes

- **scene_parser.c**
  - Added checks for null token arrays (`!tokens`) before validating token length.
  - Improved validation in `parse_ambient`, `parse_camera`, and `parse_light` to include range checks (e.g., intensity between 0.0–1.0, FOV limits, normalized orientation).
  - Refactored main parsing loop to trim newlines, strip comments, skip empty lines, and split into tokens upfront.
  - Replaced direct calls to static parsers with a unified `parse_objects(tokens[0], tokens, scene)` dispatch for `pl`, `sp`, and `cy` identifiers.
  - Removed duplicate static `parse_plane` and `parse_cylinder` implementations; those are now in `scene_parser_objects.c`.
  - Added error reporting with line numbers for invalid identifiers and formats.

- **scene_parser_objects.c**
  - Updated `parse_plane` and `parse_cylinder` signatures to accept pre-split `char **tokens` instead of raw lines.
  - Enhanced validation in each parser function and provided detailed error messages when definitions are malformed.
  - Introduced `parse_sphere(tokens, scene)` for `sp` identifier, including radius and RGB validation.
  - Re-added `parse_objects(identifier, tokens, scene)` dispatch function with `strcmp` on `"pl"`, `"sp"`, `"cy"` paths.
  - Updated function comments and author metadata in file headers.

- **scene_parser_utils.c**
  - Extended `init_scene` to initialize `num_spheres`, `spheres` pointer, and mandatory flags (`ambient_parsed`, `camera_parsed`).
  - Updated `free_scene` to free the `spheres` array along with `lights`, `planes`, and `cylinders`.
  - Implemented `add_sphere` using `realloc` and added similar dynamic-resizing logic to `add_light`, `add_plane`, and `add_cylinder`.
  - Adjusted `validate_scene` to check presence of ambient and camera definitions rather than vector normalization alone.

*These changes ensure a consistent, token-driven parser architecture, better error reporting, and dynamic scene data structures supporting spheres and cylinders.*

## Detailed Parser Analysis

### Architecture and Error Handling
1. **Tokenization Refactoring**: The parser now separates tokenization from parsing logic:
   - Input lines are pre-processed (trimming newlines, stripping comments) before tokenization
   - All parsing functions now use pre-split tokens rather than raw lines
   - Centralized error detection with accurate line numbers and descriptive messages

2. **Unified Object Parsing**: Implemented a proper dispatch system:
   - Removed duplicate parsing functions scattered across files
   - Created a single `parse_objects()` dispatcher that routes to appropriate handlers
   - Uses proper `strcmp()` comparison rather than character-by-character checks

### Memory Management Improvements
1. **Dynamic Array Handling**: Completely revamped memory allocation:
   - Switched from manual `malloc`+`memcpy`+`free` patterns to cleaner `realloc`-based approach
   - Proper initialization of all scene pointers to NULL in `init_scene()`
   - More consistent cleanup in `free_scene()` that now handles spheres

2. **Validation and Safety**: Added extensive validation:
   - Null pointer checks throughout the parsing pipeline
   - Range validation for numeric values (e.g., FOV 0-180°, intensity 0.0-1.0)
   - Vector normalization verification for orientation vectors

### New Features
1. **Sphere Support**: Added complete sphere parsing functionality:
   - New `parse_sphere()` function with radius and color validation
   - `add_sphere()` function with dynamic array management
   - Updated scene structure with sphere count and array

2. **Enhanced Debugging**: Significant improvements to error reporting:
   - Detailed error messages with context (e.g., "Invalid cylinder values (vector, color, non-normalized axis)")
   - Line number tracking in parsing errors
   - Validation flags for mandatory elements (ambient light, camera)

### Code Quality
1. **Documentation**: Added function documentation with brief descriptions and parameter details
2. **Consistent Style**: Updated author headers and standardized function structures
3. **Removed Dead Code**: Eliminated commented-out code segments and redundant checks
