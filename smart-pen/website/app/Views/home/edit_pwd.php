<?= $this->extend('layout/index') ?>

<?= $this->section('content') ?>
  <!-- // Basic multiple Column Form section start -->
  <?php //dd($devices);  ?>

  <?php if (session()->getFlashdata('pesan')) : ?>
                <div class="alert alert-danger" role="alert">
                    <?= session()->getFlashdata('pesan'); ?>
                </div>
  <?php endif; ?>

  <section id="multiple-column-form">
    <div class="row match-height">
      <div class="col-12">
        <div class="card">
          <div class="card-header">
            <h4 class="card-title">Ubah Passoword</h4>
          </div>
          
          <div class="card-content">
            <div class="card-body">
              <form class="form" method="post" action = "/update_pwd/<?= $data ?>">

                <div class="row">
                  <div class="col-md-6 col-12">
                    <div class="form-group">
                      <label for="kode_dokter">Kode Dokter</label>
                      <input
                        type="text"
                        id="kode_dokter"
                        class="form-control"
                        value="<?= $data ?>"
                        name="kode_dokter"
                        disabled
                      />
                    </div>
                  </div>

                  <div class="col-md-6 col-12">
                    <div class="form-group">
                      <label for="nama_dokter">Password Lama</label>
                      <input
                        type="password"
                        id="nama_dokter"
                        class="form-control"
                        name="old_password"
                      />
                    </div>
                  </div>

                  <div class="col-md-6 col-12">
                    <div class="form-group">
                      <label for="alamat">Password Baru</label>
                      <input
                        type="password"
                        id="alamat"
                        class="form-control"                        
                        name="password"
                      />
                    </div>
                  </div>       


                  <div class="col-md-6 col-12">
                    <div class="form-group">
                      <label for="tempat_lahir">Confir Password</label>
                      <input
                        type="password"
                        id="tempat_lahir"
                        class="form-control"
                        name="confir_password"
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