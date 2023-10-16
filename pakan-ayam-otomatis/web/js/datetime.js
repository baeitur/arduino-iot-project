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
  client.subscribe('DATE-TIME');
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

function onMessageArrived(message) {
  console.log('onMessageArrived:' + message.payloadString);
  if (message.destinationName == 'DATE-TIME') {
    alert('data berhasil si simpan');
  }
}

// fungsi untuk mengirimkan pesan ke ESP
function onPublishMessage(topic, message) {
  message = new Paho.MQTT.Message(message);
  message.destinationName = topic;
  client.send(message);
}

const submitForm = document.getElementById('inputDateTime');
submitForm.addEventListener('submit', function (event) {
  event.preventDefault();
  changeDateTime();
});

function changeDateTime() {
  const jam = document.getElementById('time').value;
  const tanggal = document.getElementById('date').value;

  let [h, m, s] = jam.split(':');
  let [thn, bln, tgl] = tanggal.split('-');
  const data = `${h} ${m} ${s} ${tgl} ${bln} ${thn}`;

  onPublishMessage('DATE-TIME', data);
}
