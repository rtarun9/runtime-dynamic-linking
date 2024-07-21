#include <stdio.h>
#include <windows.h>

// A #define that can be used to create either function signature of a
// particular type, or create a typedef that can be used to create function
// pointers.
// Heavily inspired by hand made hero (casey muratori's func pointer style).
#define GET_FUNC_SIGNATURE(name) float name(float x, float y)
typedef GET_FUNC_SIGNATURE(type_multiply_float);

GET_FUNC_SIGNATURE(stub_multiply_float)
{
    return 0.0f;
}

static type_multiply_float *pfun_multiply_float = stub_multiply_float;

// Helper functions.
void message_box(const char *message, const char *title)
{
    MessageBox(NULL, message, title, MB_OK);
}

void display_float_in_message_box(float result)
{
    char message[100];
    sprintf(message, "Result :: %f", result);

    message_box(message, "Result");
}

// Function to load the 'multiply_float' function from the dll.
void load_multiply_float_function_from_dll()
{
    // At runtime, try to load the dll.
    HMODULE sample_lib_module = LoadLibraryA("sample_lib/lib.dll");
    if (!sample_lib_module)
    {
        message_box("Failed to load sample_lib/lib.dll", "ERROR");
    }
    else
    {
        message_box("Successfully loaded sample_lib/lib.dll", "NOTE");
        type_multiply_float *pfun_multiply_float_from_lib =
            (type_multiply_float *)GetProcAddress(sample_lib_module, "multiply_float");

        if (pfun_multiply_float_from_lib == NULL)
        {
            message_box("Could not load the multiply_float function from the sample_lib/lib.dll", "NOTE");
        }

        pfun_multiply_float = pfun_multiply_float_from_lib;
    }
}

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
    display_float_in_message_box(pfun_multiply_float(10, 20));

    load_multiply_float_function_from_dll();

    display_float_in_message_box(pfun_multiply_float(10, 20));

    return 0;
}
