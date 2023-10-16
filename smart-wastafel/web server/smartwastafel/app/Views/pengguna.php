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
         <h6 class="m-0 font-weight-bold text-primary">Data Pengguna</h6>
      </div>
      <div class="card-body">
         <div class="table-responsive">
            <table class="table" id="dataTable" width="100%" cellspacing="0" style="font-family:'arial'">
               <thead class="text-dark">
                  <tr>
                     <th>#</th>
                     <th>Waktu</th>
                     <th>Pengguna</th>
                     <th>Suhu</th>
                     <th>Video</th>
                     <th>Aksi</th>
                  </tr>
               </thead>
               <tbody>
                  <?php $i = 6 * $pager->getCurrentPage('pengguna') - 5 ?>
                  <?php foreach ($data_pengguna as $k) : ?>
                     <tr>
                        <td><?= $i++; ?></td>
                        <td><?= $k['updated_at']; ?></td>
                        <td><?= $k["user"].$k['id']; ?></td>
                        <td><?= $k["suhu"]; ?></td>
                        <td>
                           <?= $k["videos"]; ?>
                           
                        </td>
                        <td class="align-items-center">
                           <a class="btn btn-dark btn-circle btn-sm" href="<?=base_url()?>/download/<?=$k['videos'];?>">
                              <i class="fas fa-download"></i>
                           </a>
                           <form action="/pengguna/<?=$k['id'];?>/<?=$k['videos'];?>" method="POST" class="d-inline">
                              <?= csrf_field(); ?>
                              <input type="hidden" name="_method" value="DELETE">
                              <button type="submit" class="btn btn-danger btn-circle btn-sm" onclick="return confirm('apakah anda yakin untuk di hapus.?')"><i class="fas fa-trash"></i></button>
                           </form>
                        </td>
                     </tr>
                  <?php endforeach; ?>
               </tbody>
            </table>
            <?= $pager->links('pengguna', 'data_pager'); ?>
         </div>
      </div>
   </div>

</div>

<?= $this->endSection(); ?>