#include <string>

namespace RendererDemo {

class Application {
public:
    Application() {};
    ~Application() {};

    void run();


private:
    std::string app_name = "RendererDemo Application";
};

}