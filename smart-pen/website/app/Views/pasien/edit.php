<?= $this->extend('layout/index') ?>

<?= $this->section('content') ?>
  <!-- // Basic multiple Column Form section start -->

  <?php if (session()->getFlashdata('pesan')) : ?>
        <div class="alert alert-danger" role="alert">
            <?= session()->getFlashdata('pesan'); ?>
        </div>
  <?php endif; ?>

  <?php if (!empty($validation->getErrors())) : ?>
        <div class="alert alert-danger" role="alert">
        <?= $validation->listErrors() ?>
        </div>
  <?php endif; ?>

  <section id="multiple-column-form">
    <div class="row match-height">
      <div class="col-12">
        <div class="card">
          <div class="card-header">
            <h4 class="card-title">Ubah Data Pasien</h4>
          </div>
          <div class="card-content">
            <div class="card-body">
              <form class="form" method = "post" action = "/update_pasien/<?= $data['id_finger'] ?>">

                <div class="row">
                  <div class="col-md-6 col-12">
                    <div class="form-group">
                      <label for="id_pasien">ID Finger</label>
                      <input
                        type="text"
                        id="id_pasien"
                        class="form-control"
                        value = "<?= $data['id_finger'] ?>"
                        name="id_finger"
                        disabled
                      />
                    </div>
                  </div>

                  <div class="col-md-6 col-12">
                    <div class="form-group">
                      <label for="no_identitas">No Identitas</label>
                      <input
                        type="text"
                        id="no_identitas"
                        class="form-control"
                        value = "<?= $data['no_identitas'] ?>"
                        name="no_identitas"
                      />
                    </div>
                  </div>

                  <div class="col-md-6 col-12">
                    <div class="form-group">
                      <label for="nama_pasien">Nama Pasien</label>
                      <input
                        type="text"
                        id="nama_pasien"
                        class="form-control"
                        value = "<?= $data['nama_pasien'] ?>"
                        name="nama_pasien"
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
                        name="alamat"
                        value = "<?= $data['alamat'] ?>"
                      />
                    </div>
                  </div>

                  <div class="col-md-6 col-12">
                    <div class="form-group">
                      <label for="jenis_kelamin">Jenis Kelamin</label>                       
                        <select class="choices form-select" name="jenis_kelamin" >
                          <option value="Laki-laki">Laki-Laki</option>
                          <option value="Perempuan">Perempuan</option>
                        </select>                        
                    </div>
                  </div>

                  <div class="col-md-6 col-12">
                    <div class="form-group">
                      <label for="golongan_darah" >Golongan Darah</label>
                        <select class="choices form-select" name="golongan_darah">
                          <option value="A">A</option>
                          <option value="B">B</option>
                          <option value="AB">AB</option>
                          <option value="O">O</option>
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
                        value = "<?= $data['tempat_lahir'] ?>"
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
                        value = "<?= $data['tanggal_lahir'] ?>"
                      />
                    </div>
                  </div>

                  <div class="col-md-6 col-12">
                    <div class="form-group">
                      <label for="agama">Agama</label>
                      <input
                        type="text"
                        id="agama"
                        class="form-control"
                        name="agama"
                        value = "<?= $data['agama'] ?>"
                      />
                    </div>
                  </div>

                  <div class="col-md-6 col-12">
                    <div class="form-group">
                      <label for="no_hp">No Telephone</label>
                      <input
                        type="text"
                        id="no_hp"
                        class="form-control"
                        name="no_telepon"
                        value = "<?= $data['no_telepon'] ?>"
                      />
                    </div>
                  </div>


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