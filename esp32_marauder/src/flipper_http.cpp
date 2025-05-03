#include "flipper_http.h"
#include "flipper_http/FlipperHTTP.h"

FlipperHTTP::FlipperHTTP *flipperHttp;

void flipper_http_setup()
{
    if (flipperHttp != nullptr)
    {
        delete flipperHttp;
    }
    flipperHttp = new FlipperHTTP::FlipperHTTP();
    flipperHttp->setup();
}

void flipper_http_loop()
{
    flipperHttp->loop();
}
