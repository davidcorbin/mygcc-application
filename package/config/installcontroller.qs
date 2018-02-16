function Controller() {}

/**
 * Skip the component selection page. When installing and uninstalling the
 * facade application, you must always include all components.
 */
Controller.prototype.ComponentSelectionPageCallback = function() {
    var widget = gui.currentPageWidget();
    widget.selectAll();
    gui.clickButton(buttons.NextButton);
}
