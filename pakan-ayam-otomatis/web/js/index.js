//membuat client baru
//client = new Paho.MQTT.Client("host", port,"client_id");
client = new Paho.MQTT.Client(
  'a59d0725a5d14015b08dfb45bc48a403.s2.eu.hivemq.cloud',
  8884,
  'learn_' + parseInt(Math.random() * 100, 10)
);

// deklarasi beberapa variabel untuk menghandle proses login
client.onConnectionLost = onConnectionLost;
client.onMessageArrived = onMessageArrived;
var options = {
  useSSL: true,
  userName: 'smartsistem0101',
  password: 'B4e1t.ur',
  onSuccess: onConnect,
  onFailure: doFail,
};

// connect the client
client.connect(options);

// fungsi jika client berhasil terhubung dengan server
function onConnect() {
  console.log('onConnect');

  //sebagai subscribe
  //client.subscribe('relay-state');
  //client.subscribe('time');
  //client.subscribe('date');
  //client.subscribe('timer1');
  //client.subscribe('timer2');
  //client.subscribe('timer3');
  //client.subscribe('tmp');

  client.subscribe('all-data');

  //sebagai publisher
  // message = new Paho.MQTT.Message("-");
  // message.destinationName = "/cloudmqtt";
  // client.send(message);
}

function doFail(e) {
  console.log(e);
}

// fungsi jika client dan server gagal terhubung
function onConnectionLost(responseObject) {
  if (responseObject.errorCode !== 0) {
    console.log('onConnectionLost:' + responseObject.errorMessage);
  }
}

// fungsi yang digunakan untuk menerima pesan (pesan dari ESP)

// jika menggunakan single topik
function onMessageArrived(message) {
  console.log('onMessageArrived:' + message.payloadString);
  let [time, date, temp, timer1, timer2, timer3, relay_state] =
    message.payloadString.split('|');
  document.getElementById('time').innerHTML = time;
  document.getElementById('date').innerHTML = date;
  document.getElementById('tmp').innerHTML = temp;
  document.getElementById('timer1').innerHTML = timer1;
  document.getElementById('timer2').innerHTML = timer2;
  document.getElementById('timer3').innerHTML = timer3;
  document.getElementById('relay-state').innerHTML = relay_state;
}

//jika menggunakan multiple topic
// function onMessageArrived(message) {
//   console.log('onMessageArrived:' + message.payloadString);
//   if (message.destinationName == 'time') {
//     document.getElementById('time').innerHTML = message.payloadString;
//   }
//   if (message.destinationName == 'date') {
//     document.getElementById('date').innerHTML = message.payloadString;
//   }
//   if (message.destinationName == 'relay-state') {
//     document.getElementById('relay-state').innerHTML = message.payloadString;
//   }
//   if (message.destinationName == 'timer1') {
//     document.getElementById('timer1').innerHTML = message.payloadString;
//   }
//   if (message.destinationName == 'timer2') {
//     document.getElementById('timer2').innerHTML = message.payloadString;
//   }
//   if (message.destinationName == 'timer3') {
//     document.getElementById('timer3').innerHTML = message.payloadString;
//   }
//   if (message.destinationName == 'tmp') {
//     document.getElementById('tmp').innerHTML = message.payloadString;
//   }
// }

// fungsi untuk mengirimkan pesan ke ESP
function onPublishMessage(topic, message) {
  message = new Paho.MQTT.Message(message);
  message.destinationName = topic;
  client.send(message);
}
