<?= $this->extend('layout/template'); ?>

<?= $this->section('content'); ?>

<div class="container-fluid">

   <?php if (session()->getFlashdata('pesan')) : ?>
      <div class="alert alert-success" role="alert">
         <?= session()->getFlashdata('pesan'); ?>
      </div>
   <?php endif; ?>


   <!-- DataTales Example -->
   <div class="card shadow mb-4">
      <div class="card-header py-3">
         <h6 class="m-0 font-weight-bold text-primary">Data Battery</h6>
      </div>
      <div class="card-body">
         <div class="table-responsive">
            <table class="table" id="dataTable" width="100%" cellspacing="0" style="font-family:'arial'">
               <thead class="text-dark">
                  <tr>
                     <th>#</th>
                     <th>Data Battery</th>
                     <th>Waktu</th>
                     <th>Aksi</th>
                  </tr>
               </thead>
               <tbody>
                  <?php $i = 6 * $pager->getCurrentPage('battery') - 5 ?>
                  <?php foreach ($data_battery as $k) : ?>
                     <tr>
                        <td><?= $i++; ?></td>
                        <td><?= $k["battery"]; ?></td>
                        <td><?= $k['updated_at']; ?></td>
                        <td class="align-items-center">
                           <form action="/battery/<?=$k['id'];?>" method="POST" class="d-inline">
                              <?= csrf_field(); ?>
                              <input type="hidden" name="_method" value="DELETE">
                              <button type="submit" class="btn btn-danger btn-circle btn-sm" onclick="return confirm('apakah anda yakin untuk di hapus.?')"><i class="fas fa-trash"></i></button>
                           </form>
                        </td>
                     </tr>
                  <?php endforeach; ?>
               </tbody>
            </table>
            <?= $pager->links('battery', 'data_pager'); ?>
         </div>
      </div>
   </div>

</div>

<?= $this->endSection(); ?>