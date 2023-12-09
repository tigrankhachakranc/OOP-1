#ifndef OOP_APPLICATION_HPP
#define OOP_APPLICATION_HPP

#include "CommandController/Controller/CommandController.hpp"
#include "Document/Document/Document.hpp"
#include "CommandController/ItemRegistry/ItemRegistry.hpp"

class Application {
public:
    static Application& getInstance();
    static Document& getDocument();
    static ItemRegistry& getItemRegistry();
    static bool& getQuit(); // TK: Do not do like this, you are breaking your encapsulation, instead you need simple Quit() method which will set your bool true 
    void exec();

public:
    Application(const Application&) =delete;
    Application& operator=(const Application&) =delete; // TK: Good!

private:
    Application();
    ~Application() =default;

private:
    CommandController controller_;
    Document document_;
    ItemRegistry itemRegistry_; // TK: Actually you do not need Item registry, you need ShapeRegistry instead.
    bool quit_;
};

#endif // OOP_APPLICATION_HPP
