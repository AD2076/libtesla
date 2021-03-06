#define TESLA_INIT_IMPL // If you have more than one file using the tesla header, only define this in the main one
#include <tesla.hpp>    // The Tesla Header


class GuiSecondary : public tsl::Gui {
public:
    GuiSecondary() {}

    virtual tsl::elm::Element* createUI() override {
        auto *rootFrame = new tsl::elm::OverlayFrame("Tesla Example", "v1.3.1 - Secondary Gui");

        rootFrame->setContent(new tsl::elm::DebugRectangle(tsl::gfx::Color{ 0x8, 0x3, 0x8, 0xF }));

        return rootFrame;
    }
};

class GuiDoubleLayout1 : public tsl::Gui {
public:
    GuiDoubleLayout1() {}

    virtual tsl::elm::Element* createUI() override {
        auto *rootFrame = new tsl::elm::DoubleSectionOverlayFrame("Tesla Example", "v1.3.1 - Double Section Gui 1", tsl::SectionsLayout::big_bottom, true);
        auto *top_list = new tsl::elm::List();
        auto *bottom_list = new tsl::elm::List();

        for (int i = 0; i < 10; i++) {
            top_list->addItem(new tsl::elm::SmallListItem("Small List Item " + std::to_string(i)));
        }

        for (int i = 0; i < 10; i++) {
            bottom_list->addItem(new tsl::elm::SmallListItem("Small List Item " + std::to_string(i)));
        }

        rootFrame->setTopSection(top_list);
        rootFrame->setBottomSection(bottom_list);

        return rootFrame;
    }
};

class GuiDoubleLayout2 : public tsl::Gui {
public:
    GuiDoubleLayout2() {}

    virtual tsl::elm::Element* createUI() override {
        auto *rootFrame = new tsl::elm::DoubleSectionOverlayFrame("Tesla Example", "v1.3.1 - Double Section Gui 2", tsl::SectionsLayout::same, true);
        auto *top_list = new tsl::elm::List();
        auto *bottom_list = new tsl::elm::List();

        for (int i = 0; i < 10; i++) {
            top_list->addItem(new tsl::elm::SmallListItem("Small List Item " + std::to_string(i)));   
        }

        for (int i = 0; i < 10; i++) {
            bottom_list->addItem(new tsl::elm::SmallListItem("Small List Item " + std::to_string(i)));
        }

        rootFrame->setTopSection(top_list);
        rootFrame->setBottomSection(bottom_list);

        return rootFrame;
    }
};

class GuiDoubleLayout3 : public tsl::Gui {
public:
    GuiDoubleLayout3() {}

    virtual tsl::elm::Element* createUI() override {
        auto *rootFrame = new tsl::elm::DoubleSectionOverlayFrame("Tesla Example", "v1.3.1 - Double Section Gui 3", tsl::SectionsLayout::big_top, true);
        auto *top_list = new tsl::elm::List();
        auto *bottom_list = new tsl::elm::List();

        for (int i = 0; i < 10; i++) {
            top_list->addItem(new tsl::elm::SmallListItem("Small List Item " + std::to_string(i)));
        }

        for (int i = 0; i < 10; i++) {
            bottom_list->addItem(new tsl::elm::SmallListItem("Small List Item " + std::to_string(i)));
        }

        rootFrame->setTopSection(top_list);
        rootFrame->setBottomSection(bottom_list);

        return rootFrame;
    }
};

class GuiTest : public tsl::Gui {
public:
    GuiTest(u8 arg1, u8 arg2, bool arg3) { }

    // Called when this Gui gets loaded to create the UI
    // Allocate all elements on the heap. libtesla will make sure to clean them up when not needed anymore
    virtual tsl::elm::Element* createUI() override {
        // A OverlayFrame is the base element every overlay consists of. This will draw the default Title and Subtitle.
        // If you need more information in the header or want to change it's look, use a HeaderOverlayFrame.
        auto frame = new tsl::elm::OverlayFrame("Tesla Example", "v1.3.0");

        // A list that can contain sub elements and handles scrolling
        auto list = new tsl::elm::List();

        // List Items
        list->addItem(new tsl::elm::CategoryHeader("List items"));

        auto *clickableListItem = new tsl::elm::ListItem("Clickable List Item", "...");
        clickableListItem->setClickListener([](u64 keys) { 
            if (keys & KEY_A) {
                tsl::changeTo<GuiSecondary>();
                return true;
            }

            return false;
        });

        list->addItem(clickableListItem);
        list->addItem(new tsl::elm::ListItem("Default List Item"));
        list->addItem(new tsl::elm::ToggleListItem("Toggle List Item", true));
        
        // Custom Drawer, a element that gives direct access to the renderer
        list->addItem(new tsl::elm::CategoryHeader("Custom Drawer", true));
        list->addItem(new tsl::elm::CustomDrawer([](tsl::gfx::Renderer *renderer, s32 x, s32 y, s32 w, s32 h) {
            renderer->drawCircle(x + 40, y + 40, 20, true, renderer->a(0xF00F));
            renderer->drawCircle(x + 50, y + 50, 20, true, renderer->a(0xF0F0));
            renderer->drawRect(x + 130, y + 30, 60, 40, renderer->a(0xFF00));
            renderer->drawString("Hello :)", false, x + 250, y + 70, 20, renderer->a(0xFF0F));
            renderer->drawRect(x + 40, y + 90, 300, 10, renderer->a(0xF0FF));
        }), 100);

        // Track bars
        list->addItem(new tsl::elm::CategoryHeader("Track bars"));
        list->addItem(new tsl::elm::TrackBar("\u2600"));
        list->addItem(new tsl::elm::StepTrackBar("\uE13C", 20));
        list->addItem(new tsl::elm::NamedStepTrackBar("\uE132", { "Selection 1", "Selection 2", "Selection 3" }));

        list->addItem(new tsl::elm::BigCategoryHeader("Multi Section Overlays"));
        
        auto *doubleSection1 = new tsl::elm::SmallListItem("Double Section", "1/3 : 2/3");
        doubleSection1->setClickListener([](u64 keys) { 
            if (keys & KEY_A) {
                tsl::changeTo<GuiDoubleLayout1>();
                return true;
            }

            return false;
        });
        list->addItem(doubleSection1);
        
        auto *doubleSection2 = new tsl::elm::SmallListItem("Double Section", "1/2 : 1/2");
        doubleSection2->setClickListener([](u64 keys) { 
            if (keys & KEY_A) {
                tsl::changeTo<GuiDoubleLayout2>();
                return true;
            }

            return false;
        });
        list->addItem(doubleSection2);

        auto *doubleSection3 = new tsl::elm::SmallListItem("Double Section", "2/3 : 1/3");
        doubleSection3->setClickListener([](u64 keys) { 
            if (keys & KEY_A) {
                tsl::changeTo<GuiDoubleLayout3>();
                return true;
            }

            return false;
        });
        list->addItem(doubleSection3);

        // Add the list to the frame for it to be drawn
        frame->setContent(list);
        
        // Return the frame to have it become the top level element of this Gui
        return frame;
    }

    // Called once every frame to update values
    virtual void update() override {

    }

    // Called once every frame to handle inputs not handled by other UI elements
    virtual bool handleInput(u64 keysDown, u64 keysHeld, touchPosition touchInput, JoystickPosition leftJoyStick, JoystickPosition rightJoyStick) override {
        return false;   // Return true here to singal the inputs have been consumed
    }
};

class OverlayTest : public tsl::Overlay {
public:
                                             // libtesla already initialized fs, hid, pl, pmdmnt, hid:sys and set:sys
    virtual void initServices() override {}  // Called at the start to initialize all services necessary for this Overlay
    virtual void exitServices() override {}  // Callet at the end to clean up all services previously initialized

    virtual void onShow() override {}    // Called before overlay wants to change from invisible to visible state
    virtual void onHide() override {}    // Called before overlay wants to change from visible to invisible state

    virtual std::unique_ptr<tsl::Gui> loadInitialGui() override {
        return initially<GuiTest>(1, 2, true);  // Initial Gui to load. It's possible to pass arguments to it's constructor like this
    }
};

int main(int argc, char **argv) {
    return tsl::loop<OverlayTest>(argc, argv);
}
