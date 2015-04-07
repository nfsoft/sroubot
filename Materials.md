# Materials #

The material consists of certain properties (ambient,diffuse,...), but not all of them has to be specified (if certain property is not specified, the value in OpenGL state machine remains unchanged).

Every model consists of meshes and each mesh has to have some material assigned.

SceneNodes can have materials assigned. This is useful for "coloring" models without having to duplicate it's geometry.

# Material Scripts #

The material scripts are of following format:

```
name[tab]material1
elem[tab]value1[tab]value2..
elem[tab]value1[tab]value2[tab]value3..

name[tab]material2
elem[tab]value1...
```

### List of supported "elements" ###
  * name - Name of the material (has to be specified prior to other properties, also serves as delimiter of individual materials)
  * ambi - Ambient
  * diff - Diffuse
  * spec - Specular
  * emis - Emission
  * shin - Shininess