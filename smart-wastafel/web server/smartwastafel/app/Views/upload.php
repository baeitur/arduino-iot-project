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
      <form method="post" action="<?= base_url(); ?>/upload" enctype="multipart/form-data">
                    <?= csrf_field(); ?>
                    <div class="mb-3">
                        <label for="berkas" class="form-label">Berkas</label>
                        <input type="file" class="form-control" id="berkas" name="file">
                    </div>
                    <div class="mb-3">
                        <label for="keterangan" class="form-label">Keterangan</label>
                        <textarea class="form-control" id="keterangan" name="keterangan" rows="3"><?= old('keterangan'); ?></textarea>
                    </div>
                    <div class="mb-3">
                        <input type="submit" class="btn btn-info" value="Upload" />
                    </div>
                </form>
      </div>
   </div>
</div>

<?= $this->endSection(); ?>