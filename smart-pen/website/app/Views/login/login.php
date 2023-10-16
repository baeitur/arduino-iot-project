<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Sign in</title>
    <link rel="stylesheet" href="<?= base_url("template")?>/assets/css/bootstrap.css">
    
    <link rel="shortcut icon" href="<?= base_url("template")?>/assets/images/favicon.svg" type="image/x-icon">
    <link rel="stylesheet" href="<?= base_url("template")?>/assets/css/app.css">
</head>

<body>
    <div id="auth">
        
<div class="container">
    <div class="row">
        <div class="col-md-5 col-sm-12 mx-auto">
            <div class="card pt-4">
                <div class="card-body">
                    <div class="text-center mb-5">
                        
                        <h3>Sign In</h3>
                        <p>Please sign in to continue to application.</p>
                    </div>

                    <?php if (session()->getFlashdata('pesan')) : ?>
                          <div class="alert alert-danger" role="alert">
                              <?= session()->getFlashdata('pesan'); ?>
                          </div>
                    <?php endif; ?>
                    
                    <form action = "/login" method = "post" >
                        <div class="form-group position-relative has-icon-left">
                            <label for="kode_dokter">Kode Dokter</label>
                            <div class="position-relative">
                                <input type="text" class="form-control" id = "kode_dokter" name = "kode_dokter">
                                <div class="form-control-icon">
                                    <i data-feather="user"></i>
                                </div>
                            </div>
                        </div>
                        <div class="form-group position-relative has-icon-left">
                            <div class="clearfix">
                                <label for="password">Password</label>                                
                            </div>
                            <div class="position-relative">
                                <input type="password" class="form-control" id="password" name="password">
                                <div class="form-control-icon">
                                    <i data-feather="lock"></i>
                                </div>
                            </div>
                        </div>                        
                        <div class="clearfix">
                            <button class="btn btn-primary float-end">Login</button>
                        </div>
                    </form>
                    
                </div>
            </div>
        </div>
    </div>
</div>

    </div>
    <script src="<?= base_url("template")?>/assets/js/feather-icons/feather.min.js"></script>
    <script src="<?= base_url("template")?>/assets/js/app.js"></script>
    
    <script src="<?= base_url("template")?>/assets/js/main.js"></script>
</body>

</html>
