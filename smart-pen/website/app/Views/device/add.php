<?= $this->extend('layout/index') ?>

<?= $this->section('content') ?>
  <!-- // Basic multiple Column Form section start -->
  <section id="multiple-column-form">
    <div class="row match-height">
      <div class="col-12">
        <div class="card">
          <div class="card-header">
            <h4 class="card-title">Tambah Data Device</h4>
          </div>
          <div class="card-content">
            <div class="card-body">
              <form class="form" method = "post" action = "<?= base_url('/save_device') ?>">

                <div class="row">
                  <div class="col-md-12 col-12">
                    <div class="form-group">
                      <label for="serial_device">Serial Device</label>
                      <input
                        type="text"
                        id="serial_device"
                        class="form-control"
                        value="<?= old('serial_device'); ?>"
                        name="serial_device"
                      />
                    </div>
                  </div>

                  <div class="col-md-6 col-12">
                    <div class="form-group">
                      <label for="start_id">Start ID</label>
                      <input
                        type="text"
                        id="start_id"
                        class="form-control"
                        value="<?= old('start_id'); ?>"
                        name="start_id"
                      />
                    </div>
                  </div>

                  <div class="col-md-6 col-12">
                    <div class="form-group">
                      <label for="end_id">End ID</label>
                      <input
                        type="text"
                        id="end_id"
                        class="form-control"
                        value="<?= old('end_id'); ?>"
                        name="end_id"
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
                    <button
                      type="reset"
                      class="btn btn-light-secondary me-1 mb-1"
                    >
                      Reset
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