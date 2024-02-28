let serial;
let serialOptions = { baudRate: 9600 }; //set baudrate

function setup() {
    createCanvas(400, 400);
    serial = new Serial(); //initialization phase
    serial.on(SerialEvents.CONNECTION_OPENED, onSerialConnectionOpened);
    serial.on(SerialEvents.CONNECTION_CLOSED, onSerialConnectionClosed);
    serial.on(SerialEvents.DATA_RECEIVED, onSerialDataReceived);
    serial.on(SerialEvents.ERROR_OCCURRED, onSerialErrorOccurred);
}

function draw() {
    //background(220); removed since I rendered the buttons using HTML and CSS
}
function onSerialErrorOccurred(eventSender, error) {
    console.log("onSerialErrorOccurred", error);
}
function onSerialConnectionOpened(eventSender) {
    console.log("onSerialConnectionOpened", eventSender);
    document.getElementById("connect-button").style.display = "none";
}
function onSerialConnectionClosed(eventSender) {
    console.log("onSerialConnectionClosed", eventSender);
}
function onSerialDataReceived(eventSender, newData) {
    console.log("onSerialDataReceived", newData);
}

function onConnectButtonClick() {
    // if (navigator.serial) {
    if (!serial.isOpen()) {
        serial.connectAndOpen(null, serialOptions);
        // await serial.connectAndOpen();
    } else {
        console.log("The serial connection appears already open");
    }

    // } else {
    //     alert("The Web Serial API does not appear supported on this web browser.");
    // }
    console.log('R U tired?');
}
function onClick(src) { 
    if (src.value == 'off') { //check current state to decide if data needs to be sent
        src.value = 'on';
        serial.writeLine(1); //write one to board
        console.log('1'); //console log data to confirm operation
        //send data
    } else {
        src.value = 'off'; //opposite procedure of the above mentioned code.
        serial.writeLine(0);
        console.log('0');
    }

}
