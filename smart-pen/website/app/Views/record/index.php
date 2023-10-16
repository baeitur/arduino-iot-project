<?= $this->extend('layout/index') ?>

<?php $this->section('content') ?>
  <div class="page-title">
      <h3>Medical Record</h3>
  </div>

  <?php //dd($datas); ?>

  <section class="section">
    
    <div class="row mb-4">
      <div class="col">                
        <div class="card">
          <div class="card-header d-flex justify-content-between align-items-center">
            <h4 class="card-title">Medical Record</h4>
            <div class="d-flex">
              <a href="<?= base_url('/add_record') ?>"><i data-feather="plus-circle"></i></a>
              <a href=""><i data-feather="download"></i></a>
            </div>
          </div>
          <div class="card-body px-0 pb-0">
            <div class="table-responsive">
              <table class="table mb-0" id="table1">
                <thead>
                  <tr>
                    <th>Nomor RM</th>
                    <th>Nama Pasien</th>                           
                    <th>Keluhan</th>
                    <th>Dokter</th>
                    <th>Aksi</th>
                  </tr>
                </thead>
                <tbody>
                <?php foreach($datas as $data):?>
                  <tr>
                    <td><?= $data["no_rm"] ?></td>
                    <td><?= $data["nama_pasien"] ?></td>
                    <td><?= $data["keluhan_utama"] ?></td>
                    <td><?= $data["nama_dokter"] ?></td>                            
                    <td>
                      <!-- Button trigger for basic modal -->
                      <button
                        type="button"
                        class=" btn btn-sm badge bg-primary"
                        data-bs-toggle="modal"
                        data-bs-target="#modal-<?=$data['no_rm']?>"
                      >
                      Detail
                      </button>

                      <!--Basic Modal -->
                      <div
                        class="modal fade text-left"
                        id="modal-<?=$data['no_rm']?>"
                        tabindex="-1"
                        role="dialog"
                        aria-labelledby="myModalLabel1"
                        aria-hidden="true"
                      >
                        <div
                          class="modal-dialog modal-dialog-scrollable"
                          role="document"
                        >
                          <div class="modal-content">
                            <div class="modal-header">
                              <h5 class="modal-title" id="myModalLabel1">
                                Detail Rekam Medis
                              </h5>
                              <button
                                type="button"
                                class="close rounded-pill"
                                data-bs-dismiss="modal"
                                aria-label="Close"
                              >
                                <i data-feather="x"></i>
                              </button>
                            </div>
                            <div class="modal-body">
                              
                              <ul class="list-group list-group-flush">
                                  <li class="list-group-item">Tempat        : <?= $data['tempat']?></li>
                                  <li class="list-group-item">Tanggal       : <?= $data['tanggal']?></li>
                                  <li class="list-group-item">No RM         : <?= $data['no_rm']?></li>
                                  <li class="list-group-item"><h5>IDENTITAS</h5></li>
                                  <li class="list-group-item">Nama          : <?= $data['nama_pasien']?></li>
                                  <li class="list-group-item"><h5>ANAMNESA</h5></li>
                                  <li class="list-group-item">Keluhan Utama : <?= $data['keluhan_utama']?></li>                                  
                                  <li class="list-group-item">RPS           : <?= $data['rsp']?></li>
                                  <li class="list-group-item">RPD           : <?= $data['rpd']?></li>
                                  <li class="list-group-item">RPK           : <?= $data['rpk']?></li>
                                  <li class="list-group-item"><h5>PEMERIKSAAN FISIK DAN VITAL SIGN</h5></li>
                                  <li class="list-group-item">TENSI         : <?= $data['tensi']?></li>
                                  <li class="list-group-item">NADI          : <?= $data['nadi']?></li>
                                  <li class="list-group-item">RR            : <?= $data['rr']?></li>
                                  <li class="list-group-item">BB            : <?= $data['bb']?></li>
                                  <li class="list-group-item">TEMPERATUR     : <?= $data['temperatur']?></li>
                                  <li class="list-group-item">GULA DARAH    : <?= $data['gula_darah']?></li>
                                  <li class="list-group-item">Dx            : <?= $data['dx']?></li>
                                  <li class="list-group-item">INJEKSI       : <?= $data['injeksi']?></li>
                                  <img src="./img/<?= $data['gambar']?>" class="card-img-top img-thumbnail" alt="...">
                              </ul>
                            </div>
                            <div class="modal-footer">
                              <button
                                type="button"
                                class="btn"
                                data-bs-dismiss="modal"
                              >
                                <i class="bx bx-x d-block d-sm-none"></i>
                                <span class="d-none d-sm-block">Close</span>
                              </button>
                            </div>
                          </div>
                        </div>
                      </div>
                      <a href="/edit_record/<?= $data['no_rm'] ?>"><span class="badge bg-success">Edit</span></a>
                      <form action="/record/<?= $data['no_rm']; ?>" method="POST" class="d-inline">
                        <?= csrf_field(); ?>
                        <input type="hidden" name="_method" value="DELETE">
                        <button type="submit" class="btn btn-sm badge bg-danger" onclick="return confirm('apakah anda yakin untuk di hapus.?')">Delete</i></button>
                      </form>
                    </td>
                  </tr>
                <?php endforeach;?>  
                </tbody>
              </table>
            </div>
          </div>
        </div>
      </div>
     
    </div>
  </section>
<?php $this->endSection()?>