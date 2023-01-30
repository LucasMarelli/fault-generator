#include <Arduino.h>
#ifndef HTML_H
#define HTML_H
const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
</head>

<body>
    <h1>Generador de defecto controlado</h1>
    <button onclick="location.href='fault';">Genera defecto!</button>
</body>

</html>
)=====";

const char FAULT_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
</head>
<body>
    <h1>REVENTÓ TODO!!</h1>
</body>
</html>
)=====";

#endif