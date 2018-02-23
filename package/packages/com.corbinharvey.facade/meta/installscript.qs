function Component() {
    // Request admin privileges
    installer.gainAdminRights();

    // If on Windows, add start menu shortcut
    if (installer.value("os") === "win") {
        component.addOperation("CreateShortcut", "@TargetDir@/facade.exe", "@StartMenuDir@/Facade.lnk");
    }
}

// Extract archive with elevated privileges
Component.prototype.createOperationsForArchive = function(archive) {
    component.addElevatedOperation("Extract", archive, "@TargetDir@");
}
