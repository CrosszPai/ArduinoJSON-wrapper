#include <Arduino.h>
#include <jsonwrapper.hpp>

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  size_t size = 1024;
  // size should be calculated by ArduinoJson Assistant https://arduinojson.org/v6/assistant/
  DynamicJsonDocument maindoc(size);
  int i[] = {1, 2, 3, 4};
  int b[2][2] = {{2, 123}, {233, 18}};
  int dictionary[3][2] = {{23, 68}, {30, 70}, {22, 21}};

  maindoc["text"] = "Hello World";
  maindoc["number"] = 23.42f;
  maindoc["boolean"] = false;
  array_add(&maindoc, "single_arr", i, sizeof(i) / sizeof(i[0]));
  maindoc["single_arr"].add(123);
  object_add(&maindoc, i, "general_obj", 4, new char *[10] { "value1", "value2", "value3", "value4" });
  bool logic[] = {true, false, false};
  auto a = new char *[10] { "a", "b", "c" };
  object_add(&maindoc, logic, "general_obj", 3, a);
  nested_array(&maindoc["test"]["two_dim_arr"], b, 2, 2);
  nested_object(&maindoc["test"]["array_of_object"], dictionary, 3, 2, new char *[10] { "temp", "hum" });
  maindoc["obj"]["nest"]["obj"]["in"] = 2;
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
    "arr_arr_nested": [
      [
        2,
        123
      ],
      [
        233,
        18
      ]
    ],
    "object_arr_nested": [
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
        "in": 2
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