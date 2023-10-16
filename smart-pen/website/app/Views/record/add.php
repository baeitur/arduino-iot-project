<?= $this->extend('layout/index') ?>

<?= $this->section('content') ?>
  <!-- // Basic multiple Column Form section start -->
  <section id="multiple-column-form">
    <div class="row match-height">
      <div class="col-12">
        <div class="card">
          <div class="card-header">
            <h2 class="card-title text-primary ">Tambah Medical Record</h2>
          </div>
          <div class="card-content">
            <div class="card-body">
              <form class="form"  action = "<?= base_url('/save_record') ?>" method="post"  enctype="multipart/form-data">

                <div class="row">
                  <div class="col-md-6 col-12">
                    <div class="form-group">
                      <label for="tanggal">Tanggal</label>
                      <input
                        type="date"
                        id="tanggal"
                        class="form-control"
                        value="<?= old('tanggal'); ?>"
                        name="tanggal"
                      />
                    </div>
                  </div>

                  <div class="col-md-6 col-12">
                    <div class="form-group">
                      <label for="tempat">Tempat</label>
                      <input
                        type="text"
                        id="tempat"
                        class="form-control"
                        value="<?= old('tempat'); ?>"
                        name="tempat"
                      />
                    </div>
                  </div>                             
                </div>  
                
              
                <h5 class="card-title">IDENTITAS</h5>

                <div class="row">
                  <div class="col-md-6 col-12">
                    <div class="form-group">
                      <label for="no_rm">No rm</label>
                      <input
                        type="text"
                        id="no_rm"
                        class="form-control"
                        value="<?= old('no_rm'); ?>"
                        name="no_rm"
                      />
                    </div>
                  </div>

                  <div class="col-md-6 col-12">
                    <div class="form-group">
                      <label for="nama_pasien">Nama Pasien</label>
                        <select class="choices form-select" name = "id_finger">
                        <?php foreach($pasiens as $pasien):?>
                          <option value="<?= $pasien['id_finger'] ?>"><?= $pasien["nama_pasien"] ?></option>                          
                        <?php endforeach;?>   
                        </select>  
                    </div>
                  </div>                 
                </div>  

                <input type="hidden" value = "123321" name = "kode_dokter">

                <h5 class="card-title">ANAMNESA</h5>

                <div class="row">
                  <div class="col-md-6 col-12">
                    <div class="form-group">
                      <label for="keluhan_utama">Keluhan Utama</label>
                      <input
                        type="text"
                        id="keluhan_utama"
                        class="form-control"
                        value="<?= old('keluhan_utama'); ?>"
                        name="keluhan_utama"
                      />
                    </div>
                  </div>

                  <div class="col-md-6 col-12">
                    <div class="form-group">
                      <label for="rsp">RSP</label>
                      <input
                        type="text"
                        id="rsp"
                        class="form-control"
                        value="<?= old('rsp'); ?>"
                        name="rsp"
                      />
                    </div>
                  </div>

                  <div class="col-md-6 col-12">
                    <div class="form-group">
                      <label for="rpd">RPD</label>
                      <input
                        type="text"
                        id="rpd"
                        class="form-control"
                        value="<?= old('rpd'); ?>"
                        name="rpd"
                      />
                    </div>
                  </div>    
                  
                  <div class="col-md-6 col-12">
                    <div class="form-group">
                      <label for="rpk">RPK</label>
                      <input
                        type="text"
                        id="rpk"
                        class="form-control"
                        value="<?= old('rpk'); ?>"
                        name="rpk"
                      />
                    </div>
                  </div>                           

                </div>
                
                <h5 class="card-title mt-3">PEMERIKSAAN FISIK DAN VITAL SIGN </h5>
                
                <div class="row">

                  <div class="col-md-6 col-12">
                    <div class="form-group">
                      <label for="tensi">Tensi (mm/Hg)</label>
                      <input
                        type="text"
                        id="tensi"
                        class="form-control"
                        value="<?= old('tensi'); ?>"
                        name="tensi"
                      />
                    </div>
                  </div>

                  <div class="col-md-6 col-12">
                    <div class="form-group">
                      <label for="nadi">Nadi (x/menit)</label>
                      <input
                        type="text"
                        id="nadi"
                        class="form-control"
                        value="<?= old('nadi'); ?>"
                        name="nadi"
                      />
                    </div>
                  </div>

                  <div class="col-md-6 col-12">
                    <div class="form-group">
                      <label for="rr">RR (x/menit)</label>
                      <input
                        type="text"
                        id="rr"
                        class="form-control"
                        value="<?= old('rr'); ?>"
                        name="rr"
                      />
                    </div>
                  </div>

                  <div class="col-md-6 col-12">
                    <div class="form-group">
                      <label for="bb">BB (kg)</label>
                      <input
                        type="text"
                        id="bb"
                        class="form-control"
                        value="<?= old('bb'); ?>"
                        name="bb"
                      />
                    </div>
                  </div>

                  <div class="col-md-6 col-12">
                    <div class="form-group">
                      <label for="temperatur">Temperatur (*C)</label>
                      <input
                        type="text"
                        id="temperatur"
                        class="form-control"
                        value="<?= old('temperatur'); ?>"
                        name="temperatur"
                      />
                    </div>
                  </div>

                  <div class="col-md-6 col-12">
                    <div class="form-group">
                      <label for="gula_darah">Gula Darah (mm/dl)</label>
                      <input
                        type="text"
                        id="gula_darah"
                        class="form-control"
                        value="<?= old('gula_darah'); ?>"
                        name="gula_darah"
                      />
                    </div>
                  </div>

                  <div class="col-md-6 col-12">
                    <div class="form-group">
                      <label for="hr">HR</label>
                      <input
                        type="text"
                        id="hr"
                        class="form-control"
                        value="<?= old('hr'); ?>"
                        name="hr"
                      />
                    </div>
                  </div>

                  <div class="col-md-6 col-12">
                    <div class="form-group">
                      <label for="dx">Dx</label>
                      <input
                        type="text"
                        id="dx"
                        class="form-control"
                        value="<?= old('dx'); ?>"
                        name="dx"
                      />
                    </div>
                  </div>
          
                </div>  
                
                <div class="row">          
                  <div class="col col-12">
                      <div class="form-group">
                        <label for="injeksi">Injeksi</label>
                        <input
                          type="text"
                          id="injeksi"
                          class="form-control"
                          value="<?= old('injeksi'); ?>"
                          name="injeksi"
                        />
                      </div>
                  </div>

                  <div class="col col-12">
                      <div class="form-group">
                        <label for="gambar">Gambar Pendukung</label>
                        <input
                          type="file" 
                          class="form-control" 
                          id="img" 
                          name="gambar" 
                          onchange="previewImg()">                      
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