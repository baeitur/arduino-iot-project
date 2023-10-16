<?= $this->extend('layout/index') ?>

<?= $this->section('content') ?>
  <!-- // Basic multiple Column Form section start -->
  <?php //dd($devices);  ?>

  <section id="multiple-column-form">
    <div class="row match-height">
      <div class="col-12">
        <div class="card">
          <div class="card-header">
            <h4 class="card-title">Ubah Data Dokter</h4>
          </div>
          <div class="card-content">
            <div class="card-body">
              <form class="form" method="post" action = "/update_dokter/<?= $data['kode_dokter'] ?>" enctype="multipart/form-data">

                <div class="row">
                  <div class="col-md-6 col-12">
                    <div class="form-group">
                      <label for="kode_dokter">Kode Dokter</label>
                      <input
                        type="text"
                        id="kode_dokter"
                        class="form-control"
                        value="<?= $data['kode_dokter']//old('kode_dokter'); ?>"
                        name="kode_dokter"
                      />
                    </div>
                  </div>

                  <div class="col-md-6 col-12">
                    <div class="form-group">
                      <label for="nama_dokter">Nama Dokter</label>
                      <input
                        type="text"
                        id="nama_dokter"
                        class="form-control"
                        value="<?= $data['nama_dokter'] //old('nama_dokter'); ?>"
                        name="nama_dokter"
                      />
                    </div>
                  </div>

                  <div class="col-md-6 col-12">
                    <div class="form-group">
                      <label for="alamat">Alamat</label>
                      <input
                        type="text"
                        id="alamat"
                        class="form-control"
                        value="<?= $data['alamat'] //old('alamat'); ?>"
                        name="alamat"
                      />
                    </div>
                  </div>               

                  <div class="col-md-6 col-12">
                    <div class="form-group">
                      <label for="jenis_kelamin">Jenis Kelamin</label>                       
                        <select class="choices form-select" name = "jenis_kelamin" >
                          <option value="Laki-laki">Laki-Laki</option>
                          <option value="Perempuan">Perempuan</option>
                        </select>                        
                    </div>
                  </div>

                  <div class="col-md-6 col-12">
                    <div class="form-group">
                      <label for="tempat_lahir">Tempat Lahir</label>
                      <input
                        type="text"
                        id="tempat_lahir"
                        class="form-control"
                        name="tempat_lahir"
                        value="<?= $data['tempat_lahir'] //old('tempat_lahir'); ?>"
                      />
                    </div>
                  </div>

                  <div class="col-md-6 col-12">
                    <div class="form-group">
                      <label for="tanggal_lahir">Tanggal Lahir</label>
                      <input
                        type="date"
                        id="tanggal_lahir"
                        class="form-control"
                        name="tanggal_lahir"
                        value="<?= $data['tanggal_lahir']  //old('tanggal_lahir'); ?>"
                      />
                    </div>
                  </div>

                  <div class="col-md-6 col-12">
                    <div class="form-group">
                      <label for="spesialisasi">Spesialisasi</label>
                      <input
                        type="text"
                        id="spesialisasi"
                        class="form-control"
                        name="spesialisasi"
                        value="<?= $data['spesialisasi'] //old('spesialisasi'); ?>"
                      />
                    </div>
                  </div>

                  <div class="col-md-6 col-12">
                    <div class="form-group">
                      <label for="no_telepon">No Telephone</label>
                      <input
                        type="text"
                        id="no_telepon"
                        class="form-control"
                        name="no_telepon"
                        value="<?= $data['no_telepon'] //old('no_telepon'); ?>"
                      />
                    </div>
                  </div>

                  <div class="col-md-6 col-12">
                    <div class="form-group">
                      <label for="serial_device">Serial Device</label>                       
                        <select class="choices form-select" name = "serial_device">
                        <?php foreach($devices as $device):?>
                          <option value="<?= $device['serial_device'] ?>"><?= $device['serial_device'] ?></option>
                        <?php endforeach;?>        
                        </select>                        
                    </div>
                  </div>

                  <div class="col-md-6 col-12">
                    <div class="form-group">
                      <label for="img">Foto</label>
                      <img src="/img/<?= $data['foto'] ?>" class="img-thumbnail img-preview">
                      <input 
                        type="file" 
                        class="form-control" 
                        id="img" 
                        name="foto" 
                        value="<?= $data['foto'] //old('no_telepon'); ?>"
                        onchange="previewImg()">
                    </div>
                  </div>

                  <input type="hidden" name="old_foto" value = "<?= $data['foto'] ?>">


                  <div class="col-12 d-flex justify-content-end">
                    <button
                      type="submit"
                      class="btn btn-primary me-1 mb-1"
                    >
                      Submit
                    </button>
                  </div>

                </div>
              </form>
            </div>
          </div>
        </div>
      </div>
    </div>
  </section>
  <!-- // Basic multiple Column Form section end -->
<?= $this->endSection()?>

<?= $this->section('js') ?>
<script>
  function previewImg() {
    const img = document.querySelector('#img');
    const imgPreview = document.querySelector('.img-preview');

        const fileFoto = new FileReader();
        fileFoto.readAsDataURL(img.files[0]);
        fileFoto.onload = function (e) {
            imgPreview.src = e.target.result;
        }
    }
</script>
<?= $this->endSection()?>