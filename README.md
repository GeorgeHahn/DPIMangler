# DPIMangler

Hooks SetProcessDPIAware and blocks future calls from reaching Windows, forcefully enabling DPI scaling for many applications.

Suitable to be injected into a process at initialization time or forcefully added to a process by adding to the import table.

Probably works with:
* Cadence OrCAD 16.6
* Dashlane
* Seafile
* SQL Server Management Studio

Probably doesn't work with:
* Photoshop
* Viber
* RuneScape

Please file an issue with the result for any applications you try this with

**Note: Before using this, make sure the application manefest does not set DpiAware to true.**

See [this blog post](http://www.genericmaker.com/2014/05/force-dpi-scaling-on-windows.html) for more information.
