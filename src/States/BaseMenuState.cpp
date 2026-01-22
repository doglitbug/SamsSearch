#include "BaseMenuState.h"

UIObject *BaseMenuState::generateTitle() {
    Title *title = new Title();
    LoaderParams parameters = LoaderParams(0, 0, 906, 131, "title");
    title->load(parameters);
    return title;
}

UIObject *BaseMenuState::generateButton(const std::string &text, const std::function<void()>& callback, int width) {
    Button *button = new Button();
    Assets::get()->createTextTexture(width, ROW_HEIGHT, text, "Text", "btn_" + text);
    Assets::get()->addBorderToExistingTexture("btn_" + text, 2);
    button->load(LoaderParams(0, 0, width, ROW_HEIGHT, "btn_" + text));
    button->setCallback(callback);
    return button;
}

UIObject *BaseMenuState::generateLabel(const std::string &text, int width) {
    Label *label = new Label();
    Assets::get()->createTextTexture(width, ROW_HEIGHT, text, "Text", "label_" + text);
    label->load(LoaderParams(0, 0, width, ROW_HEIGHT, "label_" + text));
    return label;
}

UIObject *BaseMenuState::generateLabel(bool link, int width) {
    LabelBoolean *label = new LabelBoolean();
    label->load(LoaderParams(0, 0, width, ROW_HEIGHT, "toggle_On"));
    label->setLink(link);
    return label;
}

UIObject *BaseMenuState::generateLabel(int (*link)(), int width) {
    LabelInteger *label = new LabelInteger();
    label->load(LoaderParams(0, 0, width, ROW_HEIGHT, "int_0"));
    label->setLink(link);
    return label;
}

UIObject *BaseMenuState::generateHeader(const std::string &text) {
    Label *header = new Label();
    Assets::get()->createTextTexture(HEADER_WIDTH, HEADER_HEIGHT, text, "Header", "header_" + text);
    header->load(LoaderParams(0, 0, HEADER_WIDTH, HEADER_HEIGHT, "header_" + text));
    return header;
}

void BaseMenuState::s_previousState() {
    EngineStateManager::get()->getStateMachine()->popState();
}

void BaseMenuState::s_menuToNothing() {
    //TODO Log out this usage?
}