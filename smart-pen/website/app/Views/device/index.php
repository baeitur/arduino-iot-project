<?= $this->extend('layout/index') ?>

<?php $this->section('content') ?>
  <div class="page-title">
      <h3>Data Device</h3>
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
            <h4 class="card-title">List Data Device</h4>
            <div class="d-flex">
              <a href="<?= base_url('/add_device') ?>"><i data-feather="plus-circle"></i></a>
              <a href=""><i data-feather="download"></i></a>
            </div>
          </div>
          <div class="card-body px-0 pb-0">
            <div class="table-responsive">
              <table class="table mb-0" id="table1">
                <thead>
                  <tr>
                    <th>Serial Device</th>
                    <th>Start ID</th>                           
                    <th>End ID</th>
                    <th>Status</th>
                    <th>Aksi</th>
                  </tr>
                </thead>
                <tbody>
                <?php foreach($datas as $data):?>
                  <tr>
                    <td><?= $data["serial_device"] ?></td>
                    <td><?= $data["start_id"] ?></td>
                    <td><?= $data["end_id"] ?></td>    
                    <td><?= ($data["status"]=="1")?"Ussed":"Not Use" ?></td>                      
                    <td>                      
                      <a href="/edit_device/<?= $data['serial_device']?>"><span class="badge bg-success">Edit</span></a>
                      <form action="/device/<?= $data['serial_device']; ?>" method="POST" class="d-inline">
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