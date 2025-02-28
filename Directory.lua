LocationDir = "%{wks.location}/settings"

OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

EXEDir = "%{wks.location}/bin/"..OutputDir
LibDir = "%{wks.location}/bin/"..OutputDir
DynamicDir = "%{wks.location}/bin/"..OutputDir
TargetDir = "%{wks.location}/bin/" .. OutputDir .. "/%{prj.name}"
ObjectDir = "%{wks.location}/bin/obj/" .. OutputDir .. "/%{prj.name}"


PreRoot = {}
PreRoot.DependenciesRoot = path.getabsolute("Dependencies")
PreRoot.ExtensionRoot = path.getabsolute("Extension")
PreRoot.MultiExtendDependenciesRoot = path.join(PreRoot.ExtensionRoot,"MultiExtend/Dependencies")

