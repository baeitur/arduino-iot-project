// -----------------------------
// HALAMAN WEB UNTUK SETTING JWS

char web_page[] PROGMEM = R"=====(

<!DOCTYPE HTML>
<html>
<meta name='viewport' content='width=device-width, initial-scale=1'>

<head>
<title>JWSP10</title>
<style> 
  body { 
    width: 97% ; 
    text-align: center; 
  } 
  input, select, button, textarea { 
    max-width: 100% ; 
    margin: 5px; 
    padding: 5px; 
    border-radius: 7px; 
  } 
  meter, progress, output { 
    max-width: 100% ; 
  } 
  h1 { 
    color: grey; 
  } 
  .note { 
    color: #555; 
    font-size:1em;
  } 
  .info { 
    background-color: #eee; 
    border-radius: 3px; 
    padding-top: 17px; 
    margin: 5px;} 
  .tombol { 
    background-color: #ccc; 
    margin: 20px; 
    padding: 10px; 
    border-radius: 10px; 
    text-decoration: none;
    }
  </style>
</head>

<body onload='updateData()'>

<h1>Jadwal Waktu Sholat</h1>

<div class='info'>
  <span id='day'></span>/<span id='month'></span>/<span id='year'></span><span> </span>
  <span id='hour'></span>:<span id='minute'></span>:<span id='second'></span><span> </span>
  <span id='temp'></span><span>C</span><br><br>
</div>


<h2>Ubah Waktu</h2>
<table width='100%'>
  <tr>
    <td>
      <form>
        <h4>Tanggal</h4>  
        <input type='date' name='date' min='2019-01-01'><br><br>
        <input type='submit' value='Ubah Tanggal'> 
      </form>  
    </td>
    <td>
      <form>  
        <h4>Jam</h4>
        <input type='TIME' name='time'><br><br>
        <input type='submit' value='Ubah Jam'> 
      </form>
    </td>
  </tr>
</table>

<br><br>
<hr/>
<br>

<h3>Adzan & Iqomah</h3>
<form>
<table width='100%'>
  <tr>
    <td>
      <label for="iqmhs">Subuh</label><br>
      <input id="iqmhs" placeholder="12" maxlength="2" size="3"/>
    </td>
    <td>
      <label for="iqmhd">Dzuhur</label><br>
      <input id="iqmhd" placeholder="8" maxlength="2" size="3"/>
    </td>
    <td>
      <label for="iqmha">Ashar</label><br>
      <input id="iqmha" placeholder="6" maxlength="2" size="3"/>
    </td>
  </tr>
  
  <tr>
    <td>
      <label for="iqmhm">Maghrib</label><br>
      <input id="iqmhm" placeholder="5" maxlength="2" size="3"/>
    </td>
    <td>
      <label for="iqmhi">Isya</label><br>
      <input id="iqmhi" placeholder="5" maxlength="2" size="3"/>
    </td>
    <td>
      <label for="durasiadzan">Adzan</label><br>
      <input id="durasiadzan" placeholder="2" maxlength="2" size="3"/>
    </td>
  </tr>
</table>
<br>
<div>
  <button onClick="setJws()"> Simpan </button>
</div>
</form>

<br><br>
<hr/>
<br>

<h3>Setting Jadwal</h3>
<form>
<table width='100%'>  
  <tr>
    <td>
      <label for="zonawaktu">Zona Waktu</label><br>
      <input id="zonawaktu" placeholder="7" maxlength="2" size="3"/>
    </td>
    <td colspan="2">
      <label for="hilal">Hilal</label><br>
      <input id="hilal" placeholder="2" maxlength="2" size="3"/>
    </td>
  </tr>
  
  <tr>
    <td>
      <label for="latitude">Latitude</label><br>
      <input id="latitude" placeholder="-6.165010" size="9"/>
    </td>
    <td>
      <label for="longitude">Longitude</label><br>
      <input id="longitude" placeholder="106.608892" size="9"/>
    </td>    
  </tr>
</table>
<div>
  <button onClick="setJws()"> Simpan </button>
</div>
</form>

<br>
<h3>Koreksi Jadwal</h3>
</br>

<form>
<table width='100%'>
  <tr>
    <td>
      <label for="ihtis">Shubuh</label><br>
      <input id="ihtis" placeholder="2" maxlength="3" size="4"/>
    </td>
    <td>
      <label for="ihtiq">Shuruq</label><br>
      <input id="ihtiq" placeholder="2" maxlength="3" size="4"/>
    </td>
    <td>
      <label for="ihtid">Dzuhur</label><br>
      <input id="ihtid" placeholder="2" maxlength="3" size="4"/>
    </td>
  </tr>
  
  <tr>
    <td>
      <label for="ihtia">Ashar</label><br>
      <input id="ihtia" placeholder="3" maxlength="3" size="4"/>
    </td>
    <td>
      <label for="ihtim">Magrib</label><br>
      <input id="ihtim" placeholder="3" maxlength="3" size="4"/>
    </td>
    <td>
      <label for="ihtii">Isya'</label><br>
      <input id="ihtii" placeholder="3" maxlength="3" size="4"/>
    </td>
  </tr>
</table>
<br>
<div>
  <button onClick="setJws()"> Simpan </button>
</div>
</form>

<br><br>
<hr/>
<br>

<h3>Murottal</h3>
<form>
<table width='100%'>
  <tr>
    <td>
      <label for="murottalt">Murottal Tahajjud</label><br>
      <input id="murottalt" placeholder="12" maxlength="3" size="3"/>
    </td>
    <td>
      <label for="murottals">Murottal Shubuh</label><br>
      <input id="murottals" placeholder="12" maxlength="2" size="3"/>
    </td>
    <td>
      <label for="murottald">Murottal Dzuhur</label><br>
      <input id="murottald" placeholder="8" maxlength="2" size="3"/>
    </td>
    <td>
      <label for="murottala">Murottal Ashar</label><br>
      <input id="murottala" placeholder="6" maxlength="2" size="3"/>
    </td>
  </tr>
  <t>
    <td>
      <label for="murottalm">Murottal Maghrib</label><br>
      <input id="murottalm" placeholder="5" maxlength="2" size="4"/>
    </td>
    <td>
      <label for="murottali">Murottal Isya</label><br>
      <input id="murottali" placeholder="5" maxlength="2" size="4"/>
    </td> 
    <td>
      <label for="murottalj">Murottal Jum'at</label><br>
      <input id="murottalj" placeholder="2" maxlength="2" size="4"/>
    </td>
  </tr>
</table>

<br>
<div>
  <button onClick="setMurottal()"> Simpan </button>
</div>
</form>

<br><br>
<hr/>
<br>

<h3>Jadwal Jumat</h3>
<form>
  <div width="100%">
    <label for="jpahing">Jum'at Pahing</label><br>
    <textarea style="text-align:center" cols="168" rows="2" id="jpahing" placeholder="Jum'at Pahing Imam : ... , Bilal : ... "/></textarea>
  </div>
  <div>
    <label for="jpon">Jum'at Pon</label><br>
    <textarea style="text-align:center" cols="168" rows="2" id="jpon" placeholder="Jum'at Pon Imam : ... , Bilal : ... "/></textarea>
  </div>
  <div>
   <label for="jwage">Jum'at Wage</label><br>
   <textarea style="text-align:center" cols="168" rows="2" id="jwage" placeholder="Jum'at Wage Imam : ... , Bilal : ... "/></textarea>
  </div>
  <div>
    <label for="jkliwon">Jum'at Kliwon</label><br>
    <textarea style="text-align:center" cols="168" rows="2" id="jkliwon" placeholder="Jum'at Kliwon Imam : ... , Bilal : ... "/></textarea>
  </div>
  <div>
    <label for="jlegi">Jum'at Legi</label><br>
    <textarea style="text-align:center" cols="168" rows="2" id="jlegi" placeholder="Jum'at Legi Imam : ... , Bilal : ... "/></textarea>
  </div>
  <div>
    <br>
    <button onClick="setJumat()"> Simpan </button>
  </div>
</form>

<br><br>
<hr/>
<br>

<h3>Informasi</h3>
<form>
  <div width="100%">
    <label for="namamasjid">Nama Masjid</label><br>
    <textarea style="text-align:center" cols="168" rows="2" id="namamasjid" placeholder="Masjid Al Kautsar"/></textarea>
  </div>
  <div>
    <label for="info1">Info1</label><br>
    <textarea style="text-align:center" cols="168"rows="2" id="info1" placeholder="info1"/></textarea>
  </div>
  <div>
    <label for="info2">Info2</label><br>
    <textarea style="text-align:center" cols="168"rows="2" id="info2" placeholder="info2"/></textarea>
  </div>
  <div>
    <label for="info2">Info3</label><br>
    <textarea style="text-align:center" cols="168"rows="2" id="info3" placeholder="info3"/></textarea>
  </div>
  <div>
    <br>
    <button onClick="setInfo()"> Simpan </button>
  </div>
</form>

<br><br>
<hr/>
<br>

</body>

<script>

var xmlHttp=createXmlHttpObject();

function createXmlHttpObject(){
 if(window.XMLHttpRequest){
    xmlHttp=new XMLHttpRequest();
 }else{
    xmlHttp=new ActiveXObject('Microsoft.XMLHTTP');// code for IE6, IE5
 }
 return xmlHttp;
}

function updateData() {
  prosesdatajws();
  proseswaktu();
}

function proseswaktu(){
 if(xmlHttp.readyState==0 || xmlHttp.readyState==4){
   xmlHttp.open('PUT','xmlwaktu',true);
   xmlHttp.onreadystatechange=handleServerResponseWaktu;
   xmlHttp.send(null);
 }
 setTimeout('proseswaktu()',1000);
}

function prosesdatajws(){
 if(xmlHttp.readyState==0 || xmlHttp.readyState==4){
   xmlHttp.open('PUT','xmldatajws',true);
   xmlHttp.onreadystatechange=handleServerResponseDataJWS;
   xmlHttp.send(null);
 }
}


function handleServerResponseWaktu(){
  
 if(xmlHttp.readyState==4 && xmlHttp.status==200){
   xmlResponse=xmlHttp.responseXML;

   xmldoc = xmlResponse.getElementsByTagName('Tahun');
   message = xmldoc[0].firstChild.nodeValue;
   document.getElementById('year').innerHTML=message;

   xmldoc = xmlResponse.getElementsByTagName('Bulan');
   message = xmldoc[0].firstChild.nodeValue;
   document.getElementById('month').innerHTML=message;

   xmldoc = xmlResponse.getElementsByTagName('Tanggal');
   message = xmldoc[0].firstChild.nodeValue;
   document.getElementById('day').innerHTML=message;

   xmldoc = xmlResponse.getElementsByTagName('Jam');
   message = xmldoc[0].firstChild.nodeValue;
   document.getElementById('hour').innerHTML=message;

   xmldoc = xmlResponse.getElementsByTagName('Menit');
   message = xmldoc[0].firstChild.nodeValue;
   document.getElementById('minute').innerHTML=message;

   xmldoc = xmlResponse.getElementsByTagName('Detik');
   message = xmldoc[0].firstChild.nodeValue;
   document.getElementById('second').innerHTML=message;

   xmldoc = xmlResponse.getElementsByTagName('Suhu');
   message = xmldoc[0].firstChild.nodeValue;
   document.getElementById('temp').innerHTML=message;
 } 
}


function handleServerResponseDataJWS(){
  
 if(xmlHttp.readyState==4 && xmlHttp.status==200){
   xmlResponse=xmlHttp.responseXML;

   xmldoc = xmlResponse.getElementsByTagName('IqomahSubuh');
   message = xmldoc[0].firstChild.nodeValue;
   document.getElementById('iqmhs').value=message;

   xmldoc = xmlResponse.getElementsByTagName('IqomahDzuhur');
   message = xmldoc[0].firstChild.nodeValue;
   document.getElementById('iqmhd').value=message;

   xmldoc = xmlResponse.getElementsByTagName('IqomahAshar');
   message = xmldoc[0].firstChild.nodeValue;
   document.getElementById('iqmha').value=message;

   xmldoc = xmlResponse.getElementsByTagName('IqomahMaghrib');
   message = xmldoc[0].firstChild.nodeValue;
   document.getElementById('iqmhm').value=message;

   xmldoc = xmlResponse.getElementsByTagName('IqomahIsya');
   message = xmldoc[0].firstChild.nodeValue;
   document.getElementById('iqmhi').value=message;

   xmldoc = xmlResponse.getElementsByTagName('DurasiAdzan');
   message = xmldoc[0].firstChild.nodeValue;
   document.getElementById('durasiadzan').value=message;

   xmldoc = xmlResponse.getElementsByTagName('Latitude');
   message = xmldoc[0].firstChild.nodeValue;
   document.getElementById('latitude').value=message;

   xmldoc = xmlResponse.getElementsByTagName('Longitude');
   message = xmldoc[0].firstChild.nodeValue;
   document.getElementById('longitude').value=message;

   xmldoc = xmlResponse.getElementsByTagName('ZonaWaktu');
   message = xmldoc[0].firstChild.nodeValue;
   document.getElementById('zonawaktu').value=message;

   xmldoc = xmlResponse.getElementsByTagName('Hilal');
   message = xmldoc[0].firstChild.nodeValue;
   document.getElementById('hilal').value=message;

   xmldoc = xmlResponse.getElementsByTagName('Ihtiyatis');
   message = xmldoc[0].firstChild.nodeValue;
   document.getElementById('ihtis').value=message;

   xmldoc = xmlResponse.getElementsByTagName('Ihtiyatiq');
   message = xmldoc[0].firstChild.nodeValue;
   document.getElementById('ihtiq').value=message;

   xmldoc = xmlResponse.getElementsByTagName('Ihtiyatid');
   message = xmldoc[0].firstChild.nodeValue;
   document.getElementById('ihtid').value=message;

   xmldoc = xmlResponse.getElementsByTagName('Ihtiyatia');
   message = xmldoc[0].firstChild.nodeValue;
   document.getElementById('ihtia').value=message;

   xmldoc = xmlResponse.getElementsByTagName('Ihtiyatim');
   message = xmldoc[0].firstChild.nodeValue;
   document.getElementById('ihtim').value=message;

   xmldoc = xmlResponse.getElementsByTagName('Ihtiyatii');
   message = xmldoc[0].firstChild.nodeValue;
   document.getElementById('ihtii').value=message;

   xmldoc = xmlResponse.getElementsByTagName('Murottalt');
   message = xmldoc[0].firstChild.nodeValue;
   document.getElementById('murottalt').value=message;

   xmldoc = xmlResponse.getElementsByTagName('Murottals');
   message = xmldoc[0].firstChild.nodeValue;
   document.getElementById('murottals').value=message;

   xmldoc = xmlResponse.getElementsByTagName('Murottald');
   message = xmldoc[0].firstChild.nodeValue;
   document.getElementById('murottald').value=message;

   xmldoc = xmlResponse.getElementsByTagName('Murottala');
   message = xmldoc[0].firstChild.nodeValue;
   document.getElementById('murottala').value=message;

   xmldoc = xmlResponse.getElementsByTagName('Murottalm');
   message = xmldoc[0].firstChild.nodeValue;
   document.getElementById('murottalm').value=message;

   xmldoc = xmlResponse.getElementsByTagName('Murottali');
   message = xmldoc[0].firstChild.nodeValue;
   document.getElementById('murottali').value=message;

   xmldoc = xmlResponse.getElementsByTagName('Murottalj');
   message = xmldoc[0].firstChild.nodeValue;
   document.getElementById('murottalj').value=message;

   xmldoc = xmlResponse.getElementsByTagName('Jpahing');
   message = xmldoc[0].firstChild.nodeValue;
   document.getElementById('jpahing').value=message;

   xmldoc = xmlResponse.getElementsByTagName('Jpon');
   message = xmldoc[0].firstChild.nodeValue;
   document.getElementById('jpon').value=message;

   xmldoc = xmlResponse.getElementsByTagName('Jwage');
   message = xmldoc[0].firstChild.nodeValue;
   document.getElementById('jwage').value=message;

   xmldoc = xmlResponse.getElementsByTagName('Jkliwon');
   message = xmldoc[0].firstChild.nodeValue;
   document.getElementById('jkliwon').value=message;

   xmldoc = xmlResponse.getElementsByTagName('Jlegi');
   message = xmldoc[0].firstChild.nodeValue;
   document.getElementById('jlegi').value=message;

   xmldoc = xmlResponse.getElementsByTagName('NamaMasjid');
   message = xmldoc[0].firstChild.nodeValue;
   document.getElementById('namamasjid').value=message;

   xmldoc = xmlResponse.getElementsByTagName('Info1');
   message = xmldoc[0].firstChild.nodeValue;
   document.getElementById('info1').value=message;

   xmldoc = xmlResponse.getElementsByTagName('Info2');
   message = xmldoc[0].firstChild.nodeValue;
   document.getElementById('info2').value=message;

   xmldoc = xmlResponse.getElementsByTagName('Info3');
   message = xmldoc[0].firstChild.nodeValue;
   document.getElementById('info3').value=message;
 }
 
}

function setJws() {
  
  console.log("tombol telah ditekan!");
  var iqmhs = document.getElementById("iqmhs").value;
  var iqmhd = document.getElementById("iqmhd").value;
  var iqmha = document.getElementById("iqmha").value;
  var iqmhm = document.getElementById("iqmhm").value;
  var iqmhi = document.getElementById("iqmhi").value;
  
  var durasiadzan = document.getElementById("durasiadzan").value;
  var latitude = document.getElementById("latitude").value;
  var longitude = document.getElementById("longitude").value;
  var zonawaktu = document.getElementById("zonawaktu").value;
  var hilal = document.getElementById("hilal").value;

  var ihtis = document.getElementById("ihtis").value;
  var ihtiq = document.getElementById("ihtiq").value;
  var ihtid = document.getElementById("ihtid").value;
  var ihtia = document.getElementById("ihtia").value;
  var ihtim = document.getElementById("ihtim").value;
  var ihtii = document.getElementById("ihtii").value;
    
  var datajws = {iqmhs:iqmhs, 
                 iqmhd:iqmhd, 
                 iqmha:iqmha, 
                 iqmhm:iqmhm, 
                 iqmhi:iqmhi, 
                 durasiadzan:durasiadzan,  
                 latitude:latitude, 
                 longitude:longitude, 
                 zonawaktu:zonawaktu, 
                 hilal:hilal,
                 ihtis:ihtis,
                 ihtiq:ihtiq,
                 ihtid:ihtid,
                 ihtia:ihtia,
                 ihtim:ihtim,
                 ihtii:ihtii,                 
                 };
  
  var xhr = new XMLHttpRequest();
  var url = "/simpandatajws";
  
  xhr.onreadystatechange = function() {
    if(this.onreadyState == 4  && this.status == 200) {
      console.log(xhr.responseText);
    }
  };
  xhr.open("POST", url, true);
  xhr.send(JSON.stringify(datajws));
  
};

function setMurottal() {
  
  console.log("tombol telah ditekan!");
  var murottalt = document.getElementById("murottalt").value;
  var murottals = document.getElementById("murottals").value;
  var murottald = document.getElementById("murottald").value;
  var murottala = document.getElementById("murottala").value;
  var murottalm = document.getElementById("murottalm").value;
  var murottali = document.getElementById("murottali").value;
  var murottalj = document.getElementById("murottalj").value;
    
  var datamurottal = {
                 murottalt:murottalt,
                 murottals:murottals,
                 murottald:murottald,
                 murottala:murottala,
                 murottalm:murottalm, 
                 murottali:murottali,
                 murottalj:murottalj,                 
                 };
  
  var xhr = new XMLHttpRequest();
  var url = "/simpandatamurottal";
  
  xhr.onreadystatechange = function() {
    if(this.onreadyState == 4  && this.status == 200) {
      console.log(xhr.responseText);
    }
  };
  xhr.open("POST", url, true);
  xhr.send(JSON.stringify(datamurottal));
  
};

function setJumat() {
  
  console.log("tombol telah ditekan!");
  var jpahing = document.getElementById("jpahing").value;
  var jpon    = document.getElementById("jpon").value;
  var jwage   = document.getElementById("jwage").value;
  var jkliwon = document.getElementById("jkliwon").value;
  var jlegi   = document.getElementById("jlegi").value;
    
  var datajumat = {
                 jpahing:jpahing,
                 jpon:jpon,
                 jwage:jwage,
                 jkliwon:jkliwon,
                 jlegi:jlegi,                 
                 };
  
  var xhr = new XMLHttpRequest();
  var url = "/simpandatajumat";
  
  xhr.onreadystatechange = function() {
    if(this.onreadyState == 4  && this.status == 200) {
      console.log(xhr.responseText);
    }
  };
  xhr.open("POST", url, true);
  xhr.send(JSON.stringify(datajumat));
  
};

function setInfo() {
  
  console.log("tombol telah ditekan!");
  var namamasjid = document.getElementById("namamasjid").value;
  var info1 = document.getElementById("info1").value;
  var info2 = document.getElementById("info2").value;
  var info3 = document.getElementById("info3").value;
    
  var datainfo = {                
                 namamasjid:namamasjid,
                 info1:info1,
                 info2:info2,
                 info3:info3
                 };
  
  var xhr = new XMLHttpRequest();
  var url = "/simpandatainfo";
  
  xhr.onreadystatechange = function() {
    if(this.onreadyState == 4  && this.status == 200) {
      console.log(xhr.responseText);
    }
  };
  xhr.open("POST", url, true);
  xhr.send(JSON.stringify(datainfo));
  
};


</script>

</html>


)=====";
