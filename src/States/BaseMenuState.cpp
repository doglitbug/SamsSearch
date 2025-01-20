#include "BaseMenuState.h"

UIObject *BaseMenuState::generateTitle() {
    Title *title = new Title();
    LoaderParams parameters = LoaderParams(0, 0, 906, 131, "title");
    title->load(parameters);
    return title;
}

UIObject *BaseMenuState::generateButton(const std::string &text, void (*callback)(), int width) {
    Button *button = new Button();
    AssetManager::get()->createTextTexture(width, 50, text, "Text", "btn_" + text);
    AssetManager::get()->addBorderToExistingTexture("btn_" + text, 2);
    button->load(LoaderParams(0, 0, width, 50, "btn_" + text, 0, 0));
    button->setCallback(callback);
    return button;
}

UIObject *BaseMenuState::generateLabel(const std::string &text, int width) {
    Label *label = new Label();
    AssetManager::get()->createTextTexture(width, 50, text, "Text", "label_" + text);
    label->load(LoaderParams(0, 0, width, 50, "label_" + text));
    return label;
}

UIObject *BaseMenuState::generateLabel(bool (*link)(), int width) {
    LabelBoolean *label = new LabelBoolean();
    label->load(LoaderParams(0, 0, width, 50, "toggle_On"));
    label->setLink(link);
    return label;
}

UIObject *BaseMenuState::generateLabel(int (*link)(), int width) {
    LabelInteger *label = new LabelInteger();
    label->load(LoaderParams(0, 0, width, 50, "int_0"));
    label->setLink(link);
    return label;
}

UIObject *BaseMenuState::generateHeader(const std::string &text) {
    Label *header = new Label();
    AssetManager::get()->createTextTexture(700, 150, text, "Header", "header_" + text);
    header->load(LoaderParams(0, 0, 700, 150, "header_" + text));
    return header;
}

void BaseMenuState::s_previousState() {
    EngineStateManager::get()->getStateMachine()->popState();
}

void BaseMenuState::s_menuToNothing() {
    //TODO Log out this usage?
}