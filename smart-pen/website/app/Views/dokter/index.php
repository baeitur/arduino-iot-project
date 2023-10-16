<?= $this->extend('layout/index') ?>

<?php $this->section('content') ?>
  <div class="page-title">
      <h3>Data Dokter</h3>
  </div>

  <?php if (session()->getFlashdata('pesan')) : ?>
        <div class="alert alert-success" role="alert">
            <?= session()->getFlashdata('pesan'); ?>
        </div>
  <?php endif; ?>

  <section class="section">
   
    <div class="row mb-4">
      <div class="col">                
        <div class="card">
          <div class="card-header d-flex justify-content-between align-items-center">
            <h4 class="card-title">List Data Dokter</h4>
            <div class="d-flex">
              <a href="<?= base_url('/add_dokter') ?>"><i data-feather="plus-circle"></i></a>
              <a href=""><i data-feather="download"></i></a>
            </div>
          </div>
          <div class="card-body px-0 pb-0">
            <div class="table-responsive">
              <table class="table mb-0" id="table1">
                <thead>
                  <tr>
                    <th>Kode Dokter</th>
                    <th>Nama Dokter</th>                           
                    <th>Alamat</th>
                    <th>Aksi</th>
                  </tr>
                </thead>
                <tbody>
                <?php foreach($datas as $data):?>
                  <tr>
                    <td><?= $data["kode_dokter"] ?></td>
                    <td><?= $data["nama_dokter"] ?></td>
                    <td><?= $data["alamat"] ?></td>                        
                    <td>
                      <!-- Button trigger for basic modal -->
                      <button
                        type="button"
                        class=" btn btn-sm badge bg-primary"
                        data-bs-toggle="modal"
                        data-bs-target="#modal-<?=$data['kode_dokter']?>"
                      >
                      Detail
                      </button>

                      <!--Basic Modal -->
                      <div
                        class="modal fade text-left"
                        id="modal-<?=$data['kode_dokter']?>"
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
                                Detail Dokter
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
                              <img src="./img/<?= $data['foto']?>" class="card-img-top w-50 img-thumbnail" alt="...">
                              <ul class="list-group list-group-flush">
                                  <li class="list-group-item">Kode Dokter : <?= $data['kode_dokter']?></li>
                                  <li class="list-group-item">Serial Device : <?= $data['serial_device']?></li>
                                  <li class="list-group-item">Nama Dokter : <?= $data['nama_dokter']?></li>
                                  <li class="list-group-item">Alamat : <?= $data['alamat']?></li>
                                  <li class="list-group-item">Jenis Keamin : <?= $data['jenis_kelamin']?></li>                                  
                                  <li class="list-group-item">Tempat Lahir : <?= $data['tempat_lahir']?></li>
                                  <li class="list-group-item">Tanggal Lahir : <?= $data['tanggal_lahir']?></li>
                                  <li class="list-group-item">Spesialisasi: <?= $data['spesialisasi']?></li>
                                  <li class="list-group-item">No Telephone : <?= $data['no_telepon']?></li>
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
                      <a href="/edit_dokter/<?= $data['kode_dokter'] ?>"><span class="badge bg-success">Edit</span></a>
                      <form action="/dokter/<?= $data['kode_dokter']; ?>" method="POST" class="d-inline">
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