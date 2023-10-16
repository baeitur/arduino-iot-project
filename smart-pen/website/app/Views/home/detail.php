<?= $this->extend('layout/index') ?>

<?php $this->section('content') ?>
  
  <?php if (session()->getFlashdata('pesan')) : ?>
        <div class="alert alert-danger" role="alert">
            <?= session()->getFlashdata('pesan'); ?>
        </div>
  <?php endif; ?>

  <section class="section">

  <?php //dd($data); ?>
    
    <div class="row mb-4">
      <div class="col">                
        <div class="card">
          <div class="card-header d-flex justify-content-between align-items-center">
            <h4 class="card-title">The Real Medical Record Detection</h4>           
          </div>
          <div class="card-body px-0 pb-0">                       
            <ul class="list-group list-group-flush m-5">
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
                <img src="/img/<?= $data['gambar']?>" class="card-img-top img-thumbnail" alt="...">
            </ul>   
          </div>
        </div>
      </div>
     
    </div>
  </section>
<?php $this->endSection()?>