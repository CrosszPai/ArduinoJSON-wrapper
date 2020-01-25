#include <Arduino.h>
#include <jsonwrapper.hpp>

void setup()
{
  json j;
  // put your setup code here, to run once:
  Serial.begin(9600);
  size_t size = 1024;
  // size should be calculated by ArduinoJson Assistant https://arduinojson.org/v6/assistant/
  DynamicJsonDocument maindoc(size);
  int i[] = {1, 2, 3, 4};
  int b[2][3] = {{2, 12, 123}, {233, 18, 123}};
  int dictionary[3][2] = {{23, 68}, {30, 70}, {22, 21}};
  auto dict_key(unique_ptr<char *>(new char *[10] { "temp", "hum" }));
  maindoc["text"] = "Hello World";
  maindoc["number"] = 23.42f;
  maindoc["boolean"] = false;
  j.array_add(&maindoc, "single_arr", i, sizeof(i) / sizeof(i[0]));
  maindoc["single_arr"].add(123);
  auto tchar(unique_ptr<char *>(new char *[10] { "value1", "value2", "value3", "value4" }));
  j.object_add(&maindoc, i, "general_obj", 4, tchar.raw_ptr());
  bool logic[] = {true, false, false};
  auto a(unique_ptr<char *>(new char *[10] { "a", "b", "c" }));
  j.object_add(&maindoc, logic, "general_obj", 3, a.raw_ptr());
  auto w = maindoc["test"]["arr_arr"];
  j.nested_array(&w, b, 2, 3);
  auto aw = maindoc["test"]["arr_obj"];
  j.nested_object(&aw, dictionary, 3, 2, dict_key.raw_ptr());
  maindoc["obj"]["nest"]["obj"]["in"] = 2;
  maindoc["obj"]["nest"]["obj"]["in"] = false;
  serializeJsonPretty(maindoc, Serial);
  /*
  {
  "text": "Hello World",
  "number": 23.42,
  "boolean": false,
  "single_arr": [
    1,
    2,
    3,
    4,
    123
  ],   
  "general_obj": {
    "value1": 1,
    "value2": 2,
    "value3": 3,
    "value4": 4,
    "a": true,
    "b": false,
    "c": false
  },
  "test": {
    "arr_arr": [
      [
        2,
        12,
        123
      ],
      [
        233,
        18,
        123
      ]
    ],
    "arr_obj": [
      {
        "temp": 23,
        "hum": 68
      },
      {
        "temp": 30,
        "hum": 70
      },
      {
        "temp": 22,
        "hum": 21
      }
    ]
  },
  "obj": {
    "nest": {
      "obj": {
        "in": false
      }
    }
  }
}
*/
}

void loop()
{
  // put your main code here, to run repeatedly:
}
