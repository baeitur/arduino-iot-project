<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
    <meta name="description" content="">
    <meta name="author" content="">

    <title>Login</title>

    <!-- Custom fonts for this template-->
    <link href="<?= base_url(); ?>/template/vendor/fontawesome-free/css/all.min.css" rel="stylesheet" type="text/css">
    <!-- <link href="https://fonts.googleapis.com/css?family=Nunito:200,200i,300,300i,400,400i,600,600i,700,700i,800,800i,900,900i" rel="stylesheet"> -->

    <style>
        @media (max-width: 576px) {
            .card .col_3 {
                display: none;
            }
        }
    </style>

    <!-- Custom styles for this template-->
    <link href="<?= base_url(); ?>/template/css/sb-admin-2.min.css" rel="stylesheet">
    
  </head>

  <body >
    <div class="container">
      <div class="row">
        <div class="col-md-6 mx-auto mt-5">
          <?php
          if(session()->getFlashdata('pesan')){ ?>
          <div class="alert alert-info">
              <?= session()->getFlashdata('pesan') ?>
          </div>
          <?php } ?>
          <form method="post"  action="<?=base_url()?>/login/auth">
            <h1 class="h3 mb-3 font-weight-normal">Login</h1>
            <div class="form-group">
              <label>Username</label>
              <input type="text" class="form-control" name="username" required="" placeholder="Masukkan Username">
            </div>
            <div class="form-group">
              <label>Password</label>
              <input type="password" class="form-control" name="password" required="" placeholder="Masukkan Password">
            </div>
            <div class="form-group">
              <button class="btn btn-primary btn-block" type="submit">Login</button>
            </div>
          </form>
        </div>
      </div>  
    </div>
  </body>
</html>