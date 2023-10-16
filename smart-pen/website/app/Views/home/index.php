<?= $this->extend('layout/index') ?>

<?php $this->section('content') ?>
  
  <?php if (session()->getFlashdata('pesan')) : ?>
        <div class="alert alert-danger" role="alert">
            <?= session()->getFlashdata('pesan'); ?>
        </div>
  <?php endif; ?>

  <section class="section">
    
    <div class="row mb-4">
      <div class="col">                
        <div class="card">
          <div class="card-header d-flex justify-content-between align-items-center">
            <h4 class="card-title">The Real Medical Record Detection</h4>
            <div class="d-flex">
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
                      <a href="/detail/<?= $data["no_rm"] ?>" type="button" class=" btn btn-sm badge bg-primary">Detail</a>                                   
                      
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
<?php
    $url1=$_SERVER['REQUEST_URI'];
    header("Refresh: 5; URL=$url1");
?>