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
  //sebagai publisher
  // message = new Paho.MQTT.Message("-");
  // message.destinationName = "/cloudmqtt";
  // client.send(message);
  client.subscribe('TIMER');
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
// function onMessageArrived(message) {
//   console.log('onMessageArrived:' + message.payloadString);
//   document.getElementById('time').innerHTML = message.payloadString;
// }

//jika menggunakan multiple topic
function onMessageArrived(message) {
  console.log('onMessageArrived:' + message.payloadString);
  if (message.destinationName == 'TIMER') {
    alert('data berhasil si simpan');
  }
}

// fungsi untuk mengirimkan pesan ke ESP
function onPublishMessage(topic, message) {
  message = new Paho.MQTT.Message(message);
  message.destinationName = topic;
  client.send(message);
}

const submitForm = document.getElementById('inputTimer');
submitForm.addEventListener('submit', function (event) {
  event.preventDefault();
  changeTimer();
});

function changeTimer() {
  const on1 = document.getElementById('on1').value;
  const off1 = document.getElementById('off1').value;
  const on2 = document.getElementById('on2').value;
  const off2 = document.getElementById('off2').value;
  const on3 = document.getElementById('on3').value;
  const off3 = document.getElementById('off3').value;

  let [hon1, mon1] = on1.split(':');
  let [hoff1, moff1] = off1.split(':');
  let [hon2, mon2] = on2.split(':');
  let [hoff2, moff2] = off2.split(':');
  let [hon3, mon3] = on3.split(':');
  let [hoff3, moff3] = off3.split(':');

  let ON1 = parseInt(hon1) * 100 + parseInt(mon1);
  let OFF1 = parseInt(hoff1) * 100 + parseInt(moff1);
  let ON2 = parseInt(hon2) * 100 + parseInt(mon2);
  let OFF2 = parseInt(hoff2) * 100 + parseInt(moff2);
  let ON3 = parseInt(hon3) * 100 + parseInt(mon3);
  let OFF3 = parseInt(hoff3) * 100 + parseInt(moff3);

  const data = `{\"on1\":\"${ON1}\",\"off1\":\"${OFF1}\",\"on2\":\"${ON2}\",\"off2\":\"${OFF2}\",\"on3\":\"${ON3}\",\"off3\":\"${OFF3}\"}`;
  onPublishMessage('TIMER', data);
}
