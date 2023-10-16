<?= $this->extend('layout/template'); ?>

<?= $this->section('content'); ?>

<div class="container-fluid">

   <?php if (session()->getFlashdata('pesan')) : ?>
      <div class="alert alert-success" role="alert">
         <?= session()->getFlashdata('pesan'); ?>
      </div>
   <?php endif; ?>


   <!-- Page Heading -->
   <?php if (session()->get('username')=='admin'):?>
      <div class="row align-items-between">
         <div class="col-sm-9">
            
         </div>
         <div class="col-sm-3">
            <a class="btn btn-primary btn-block mb-2" href="<?=base_url()?>/users/create">Tambah Data</a>
         </div>
      </div>
   <?php endif; ?>


   <!-- DataTales Example -->
   <div class="card shadow mb-4">
      <div class="card-header py-3">
         <h6 class="m-0 font-weight-bold text-primary">Data Admin</h6>
      </div>
      <div class="card-body">
         <div class="table-responsive">
            <table class="table" id="dataTable" width="100%" cellspacing="0" style="font-family:'arial'">
               <thead class="text-dark">
                  <tr>
                     <th>#</th>
                     <th>Name</th>
                     <th>Username</th>
                     <th>Password</th>
                     <th>Aksi</th>
                  </tr>
               </thead>
               <tbody>
                  <?php $i = 6 * $pager->getCurrentPage('users') - 5 ?>
                  <?php foreach ($data_users as $u) : ?>
                     <tr>
                        <td><?= $i++; ?></td>
                        <td><?= $u["name"]; ?></td>
                        <td><?= $u['username']; ?></td>
                        <td><?= $u['password']; ?></td>
                        <?php if(session()->get('username')=='admin'):?>
                           <td class="align-items-center">
                              <form action="/users/<?=$u['id'];?>" method="POST" class="d-inline">
                                 <?= csrf_field(); ?>
                                 <input type="hidden" name="_method" value="DELETE">
                                 <button type="submit" class="btn btn-danger btn-circle btn-sm" onclick="return confirm('apakah anda yakin untuk di hapus.?')"><i class="fas fa-trash"></i></button>
                              </form>
                           </td>
                        <?php endif;?>
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