#include <furi.h>
#include <input/input.h>

typedef struct {
    GpioPin* led;
    GpioPin* vibro;
} Ctx;

static void button_handler(const void* value, void* _ctx) {
    const InputEvent* event = value;
    Ctx* ctx = (Ctx*)_ctx;

    if(event->input == InputOk) {
        gpio_write(ctx->vibro, event->state);
        gpio_write(ctx->led, !event->state);
    }
}

void application_vibro(void* p) {
    Ctx ctx = {.led = (GpioPin*)&led_gpio[1], .vibro = (GpioPin*)&vibro_gpio};

    gpio_init(ctx.led, GpioModeOutputOpenDrain);
    gpio_init(ctx.vibro, GpioModeOutputPushPull);
    gpio_write(ctx.led, true);
    gpio_write(ctx.vibro, false);

    // subscribe on buttons
    PubSub* event_record = furi_record_open("input_events");
    furi_check(event_record);
    subscribe_pubsub(event_record, button_handler, &ctx);

    while(1) {
        osDelay(osWaitForever);
    }
}