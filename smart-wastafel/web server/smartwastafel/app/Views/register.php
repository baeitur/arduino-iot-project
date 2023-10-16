<?= $this->extend('layout/template'); ?>

<?= $this->section('content'); ?>

<div class="container-fluid">

   <?php //dd($validation->getError('username'));?>

   <?php if (session()->getFlashdata('pesan')) : ?>
      <div class="alert alert-success" role="alert">
         <?= session()->getFlashdata('pesan'); ?>
      </div>
   <?php endif; ?>


   <!-- DataTales Example -->
   <div class="card shadow mb-4">
      <div class="card-header py-3">
         <h6 class="m-0 font-weight-bold text-primary">Tambah Data User</h6>
      </div>
      <div class="card-body">
         <form action="<?=base_url()?>/users/save" method="post">
         <div class="form-group row">
            <label for="name" class="col-sm-2 col-form-label">Nama</label>
            <div class="col-sm-10">
               <input type="text" class="form-control <?= ($validation->hasError('name')) ? 'is-invalid' : ''; ?>" name="name" value="<?= old('name') ?>">
               <div class="invalid-feedback">
					   <?= $validation->getError('name'); ?>
				   </div>
            </div>
            
         </div>
         <div class="form-group row">
            <label for="username" class="col-sm-2 col-form-label">Username</label>
            <div class="col-sm-10">
               <input type="text" class="form-control <?= ($validation->hasError('username')) ? 'is-invalid' : ''; ?>" name="username" value="<?= old('username') ?>">
               <div class="invalid-feedback">
                  <?= $validation->getError('username'); ?>
               </div>
            </div>
         </div>
         <div class="form-group row">
            <label for="password" class="col-sm-2 col-form-label">Password</label>
            <div class="col-sm-10">
               <input type="password" class="form-control <?= ($validation->hasError('password')) ? 'is-invalid' : ''; ?>" name="password" value="<?= old('password') ?>" id="password">
               <div class="invalid-feedback">
                  <?= $validation->getError('password'); ?>
               </div>            
            </div>
         </div>
         <div class="form-group row">
            <div class="col-sm-10">
               <button type="submit" class="btn btn-primary">Tambah Data</button>
            </div>
         </div>
         </form>
      </div>
   </div>
</div>

<?= $this->endSection(); ?>