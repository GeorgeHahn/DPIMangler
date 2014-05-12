# DPIMangler

Hooks SetProcessDPIAware and blocks future calls from reaching Windows, forcefully enabling DPI scaling for many applications.

Suitable to be injected into a process at initialization time or forcefully added to a process by adding to the import table.

See [this blog post](http://www.genericmaker.com/2014/05/force-dpi-scaling-on-windows.html) for more information.
