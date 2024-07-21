#include <string.h>
#include <windows.h>

typedef float (*secret_key_function)(float, float);
secret_key_function secret_key_function_ptr = NULL;

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline,
                     int cmdshow) {
  if (secret_key_function_ptr == NULL) {
    MessageBox(NULL, "secret_key_function_ptr is NULL initially", "NOTE",
               MB_OK);
  }

  // At runtime, try to load the dll.
  HMODULE sample_lib_module = LoadLibraryA("sample_lib/lib.dll");
  if (!sample_lib_module) {
    MessageBox(NULL, "Failed to load sample_lib/lib.dll", "ERROR", MB_OK);
  } else {
    MessageBox(NULL, "Loaded sample_lib/lib.dll", "NOTE", MB_OK);
    void *p = GetProcAddress(sample_lib_module,
                             "get_the_secret_key_multiplied_by_x_and_y");
    if (p == NULL) {
      MessageBox(NULL,
                 "Failed to find the get_secret_key_multiplied_by_x_and_y "
                 "function from sample_lib/lib.dll",
                 "ERROR", MB_OK);
    }

    secret_key_function_ptr = p;
    const float res = secret_key_function_ptr(3, 10);
  }

  return 0;
}
