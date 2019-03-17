Blender is a 3D Creation/Animation/Publishing System.
[wiki](https://wiki.blender.org/index.php/Main_Page)
Application:
+ 3D movie
+

### Learn Note
##### default-screen-layout, editor-types in 5 areas (but they can be various)
    1. top, Info-Editor
    2. bottom, Timeline-Editor
    3. left, 3D-View-Editor
    4. right-upper, Outliner-Editor
    5. right-lower, Propertie-Editor
##### area inferface manipulate
    + swallon
    + resize
    + duplicate

##### Info-Editor
+ Info-Editor =+ Choose Screen Layout, 7 kind of layouts can be choose
+ Info-Editor =+ File =+ Load Factory Settings
+ Info-Editor =+ File =+ User Preferences =+ File =+ Save & Load =+ Load UI (un-choose-it)

+ Resize the font in toolbar-EditorTypes
+ Re-position the bar in toolbar-EditorTypes
+ Vertial/Horizontal Align in toolbar-EditorTypes
+ tips show on in toolbar-EditorTypes

### 3D-View
+ 3D-View-Editor =+ Window =+ Duplicate Window
+ Hotkey-T toggle tools in 3D-View-Editor
+ Hotkey-N toggle properties in 3D-View-Editor

+ Ctrl-MouseScroll, left & right horizantol move the view
+ Shift-MouseScroll, top & bottom vertical move the view

+ 3D-View-Editor core-elements
    + current scene (on Info-Editor)
    + statistics information (on Info-Editor)
    + user persp
    + (vdieo frame number) objectName, bottom-left in 3D-View-Editor
    + 3D-cursor
    + 3D-cursor-location
    + object-location, orange-origin-point
    + Grid-Floor, which is XY-plane,Z=0

+ 3D-View =+ View =+ Toggle Quad View
+ 3D-View =+ Navigation =+ Walk Navigation, WASD & QE
+ highly-restore primary-3d-visual-angle
    numpad: 03488
    3D-View =+ {Camera, Left, Navigation{Orbit-Left, Orbit-Top, Orbit-Top}}

##### Selected Objects Manipulation
+ Duplicate (HotKey:S-D)
    + 3D-View =+ Object =+ Duplicate
    + 3D-View =+ Tool Shelf =+ Duplicate
+ Delete (HotKey:X)
    + 3D-View =+ Object =+ Delete
    + 3D-View =+ Tool Shelf =+ Delete
+ Transform Items { Location, Rotation, Scale }
    + 3D-View =+ Properties =+ Transform{}
    + Properties =+ Object =+ Transform{}
+ 3D-View =+ Object =+ { Undo History, Undo, Redo }

+ Move Objects with limited axis: HotKey:G > HotKey:{X, Y, Z}
+ Move Objects with limited plane: HotKey:G > HotKey:{S-X, S-Y, S-Z}
+ Rotate Objects with limited axis: HotKey:R > HotKey:{X, Y, Z}
+ Scale Objects with limited plane: HotKey:S > HotKey:{S-X, S-Y, S-Z}
+ Scale Objects with limited axis: HotKey:S > HotKey:{X, Y, Z}
+ Rotate Object with limited plane: HotKey:R > HotKey:{S-X, S-Y, S-Z}
+ Clear {Move, Rotate, Scale}: HotKey:Alt+{G, R, S}
+ Object Handle Mode
    {Weight Paint, Texture Paint, Vertex Paint,
        Sculpt Mode, Edit Mode, Object Mode}

##### Pattern and Method
+ 3D-View =+ Object =+ Snap =+ Selection to Grid, Snap selected item(s) to nearest grid node
+ 3D-View =+ Object =+ Snap =+ Selection to Cursor, Snap selected item(s) to cursor
+ 3D-View =+ Object =+ Snap =+ Cursor to Selected, Snap cursor to center of selected item(s)
+ 3D-View =+ Object =+ Snap =+ Cursor to Center, Snap cursor to the center
+ 3D-View =+ Object =+ Snap =+ Cursor to Grid, Snap cursor to nearest grid node
+ 3D-View =+ Object =+ Snap =+ Cursor to Active, Snap cusor to active item

+ 3D-View =+ Pirot Point =+
    {Active Element, Median Point, Individual Origins, 3D Cursor, Bounding Box Center}
    {rotation, scale} for multi-selected objects pirot point
+ 3D-View =+ Transform Orientation =+
    {View, Normal, Gimbal, local, Global}
+ 3D-View =+ Two-Layers-Bar
    {    1- 5,  6-10        == Hot ==\  {       1-5,    6-0
        11-15, 16-20    }   == Key ==/    Alt+{1-5}, Alt+{6-0}  }
+ 3D-View =+ Object =+ Move to Layer
+ Info =+ Scene =+ New Scene =+
    + New,              new blank-scene
    + Link Object,      link all the objects
    + Full Copy,
    + Link Object Data, duplicate all the objects
    + Copy Settings,
+ Object Data is independent from its Transform
+ Properties =+ Display Type

##### Multi Objects
+ mulit-stack-objects selection: Alt + MouseRight
+ Circle Select, Border Select, Lasso Select
    Circle & Borde = {MouseMedium means deselect, MouseLeft means select}
    Lasso Select = {Ctrl-MouseLeft means select, Ctrl-Shift-MoseLeft means deselect}
+ 3D-View =+ Object =+ Transform =+ Align Objects,
    Bottom of 3D-View-Left-Tool-Shelf =+ Align Parameters
+ 3D-View =+ Object =+ Transform =+ Randomize Transform
    Bottom of 3D-View-Left-Tool-Shelf =+ Align Parameters
    Edit the RotationXYZ, LocationXYZ, ScaleXYZ can create Randmoize Transform Objects
+ 3D-View =+ Object =+ Transform =+ Bend
+ 3D-View =+ Object =+ Transform =+ Shear
+ 3D-View =+ Object =+ Transform =+ To Sphere
+ 3D-View =+ Join

##### relationship

##### Objects Edit Mode
