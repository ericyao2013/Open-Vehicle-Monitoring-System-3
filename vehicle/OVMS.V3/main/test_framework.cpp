/*
;    Project:       Open Vehicle Monitor System
;    Date:          14th March 2017
;
;    Changes:
;    1.0  Initial release
;
;    (C) 2011       Michael Stegen / Stegen Electronics
;    (C) 2011-2017  Mark Webb-Johnson
;    (C) 2011        Sonny Chen @ EPRO/DX
;
; Permission is hereby granted, free of charge, to any person obtaining a copy
; of this software and associated documentation files (the "Software"), to deal
; in the Software without restriction, including without limitation the rights
; to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
; copies of the Software, and to permit persons to whom the Software is
; furnished to do so, subject to the following conditions:
;
; The above copyright notice and this permission notice shall be included in
; all copies or substantial portions of the Software.
;
; THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
; IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
; FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
; AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
; LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
; OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
; THE SOFTWARE.
*/

#include <stdio.h>
#include "esp_system.h"
#include "esp_event.h"
#include "esp_event_loop.h"
#include "esp_deep_sleep.h"
#include "test_framework.h"
#include "command.h"

void test_deepsleep(int verbosity, OvmsWriter* writer, int argc, const char* const* argv)
  {
  int sleeptime = 60;
  if (argc==1)
    {
    sleeptime = atoi(argv[0]);
    }
  writer->puts("Entering deep sleep...");
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  esp_deep_sleep(1000000LL * sleeptime);
  }

class TestFrameworkInit
  {
  public: TestFrameworkInit();
} MyTestFrameworkInit  __attribute__ ((init_priority (5000)));

TestFrameworkInit::TestFrameworkInit()
  {
  puts("Initialising TEST Framework");
  OvmsCommand* cmd_test = MyCommandApp.RegisterCommand("test","Test framework",NULL);
  cmd_test->RegisterCommand("sleep","Test Deep Sleep",test_deepsleep);
  }
