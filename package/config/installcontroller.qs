function Controller() {
}

/**
 * Set the text on the introduction page
 */
Controller.prototype.IntroductionPageCallback = function() {
	var widget = gui.currentPageWidget();
	if (widget != null) {
		widget.title = "Facade Setup";

		if (installer.value("os") === "win") {
			widget.MessageLabel.setText("Welcome to Facade, the desktop application for mygcc.\n\nIMPORTANT: If you see an error throughout the install process, please rerun the installer by right-clicking on the installer and choosing 'Run as administrator'.");
		} else  {
			widget.MessageLabel.setText("Welcome to Facade, the desktop application for mygcc. Please continue through the installer and you will soon be ready to start using Facade.");
		}   
	}
}

/**
 * Skip the choose target directory page.
 */
Controller.prototype.TargetDirectoryPageCallback = function() {
	if (installer.value("os") === "win") {
		gui.clickButton(buttons.NextButton);
	}
}

/**
 * Skip the component selection page. When installing and uninstalling the
 * facade application, you must always include all components.
 */
Controller.prototype.ComponentSelectionPageCallback = function() {
	var widget = gui.currentPageWidget();
	widget.selectAll();
	gui.clickButton(buttons.NextButton);
}

/**
 * Skip the start menu directory page.
 */
Controller.prototype.StartMenuDirectoryPageCallback = function() {
	var widget = gui.currentPageWidget();
	gui.clickButton(buttons.NextButton);
}