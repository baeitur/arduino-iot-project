<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title><?= $title ?></title>

    <link rel="stylesheet" href="<?= base_url("template")?>/assets/css/bootstrap.css" />

    <link rel="stylesheet" href="<?= base_url("template")?>/assets/vendors/chartjs/Chart.min.css" />

    <link
      rel="stylesheet"
      href="<?= base_url("template")?>/assets/vendors/perfect-scrollbar/perfect-scrollbar.css"
    />
    <link rel="stylesheet" href="<?= base_url("template")?>/assets/css/app.css" />
    <link
      rel="shortcut icon"
      href="<?= base_url("template")?>/assets/images/favicon.svg"
      type="image/x-icon"
    />
  </head>
  <body>
    <div id="app">
      <div id="sidebar" class="active">
        <div class="sidebar-wrapper active">
          <div class="sidebar-header">
            <img src="<?= base_url("template")?>/assets/images/logo.svg" alt="" srcset="" />
          </div>
          <div class="sidebar-menu">
            <ul class="menu">
              <li class="sidebar-title">Main Menu</li>

              <?php if(session()->get("user_akses") == "dokter"): ?>
              <li class="sidebar-item ">
                <a href="<?= base_url('/') ?>" class="sidebar-link">
                  <i data-feather="bar-chart-2" width="20"></i>
                  <span>Home</span>
                </a>
              </li>

              <li class="sidebar-item">
                <a href="<?= base_url('/pasien') ?>" class="sidebar-link">
                  <i data-feather="users" width="20"></i>
                  <span>Data Pasien</span>
                </a>
              </li>

              <li class="sidebar-item ">
                <a href="<?= base_url('/record') ?>" class="sidebar-link">
                  <i data-feather="headphones" width="20"></i>
                  <span>Medical Record</span>
                </a>
              </li>
              <?php endif; ?>
              <?php if(session()->get("user_akses") == "admin"): ?>    
              <li class="sidebar-item">
                <a href="<?= base_url('/device') ?>" class="sidebar-link">
                  <i data-feather="edit-3" width="20"></i>
                  <span>Device Pen</span>
                </a>
              </li>

              <li class="sidebar-item">
                <a href="<?= base_url('/dokter') ?>" class="sidebar-link">
                  <i data-feather="user" width="20"></i>
                  <span>Data Dokter</span>
                </a>
              </li>
              <?php endif; ?>
              
            </ul>
          </div>
          <button class="sidebar-toggler btn x">
            <i data-feather="x"></i>
          </button>
        </div>
      </div>
      <div id="main">
        <nav class="navbar navbar-header navbar-expand navbar-light">
          <a class="sidebar-toggler" href="#"
            ><span class="navbar-toggler-icon"></span
          ></a>
          <button
            class="btn navbar-toggler"
            type="button"
            data-bs-toggle="collapse"
            data-bs-target="#navbarSupportedContent"
            aria-controls="navbarSupportedContent"
            aria-expanded="false"
            aria-label="Toggle navigation"
          >
            <span class="navbar-toggler-icon"></span>
          </button>
          <div class="collapse navbar-collapse" id="navbarSupportedContent">
            <ul
              class="navbar-nav d-flex align-items-center navbar-light ms-auto"
            >
              <li class="dropdown nav-icon">
                <a
                  href="#"
                  data-bs-toggle="dropdown"
                  class="nav-link dropdown-toggle nav-link-lg nav-link-user"
                >
                  <div class="d-lg-inline-block">
                    <i data-feather="bell"></i>
                  </div>
                </a>
                <div
                  class="dropdown-menu dropdown-menu-end dropdown-menu-large"
                >
                  <h6 class="py-2 px-4">Notifications</h6>
                  <ul class="list-group rounded-none">
                    <li class="list-group-item border-0 align-items-start">
                      <div class="avatar bg-success me-3">
                        <span class="avatar-content"
                          ><i data-feather="shopping-cart"></i
                        ></span>
                      </div>
                      <div>
                        <h6 class="text-bold">New Order</h6>
                        <p class="text-xs">
                          An order made by Ahmad Saugi for product Samsung
                          Galaxy S69
                        </p>
                      </div>
                    </li>
                  </ul>
                </div>
              </li>
              
              <li class="dropdown">
                <a
                  href="#"
                  data-bs-toggle="dropdown"
                  class="nav-link dropdown-toggle nav-link-lg nav-link-user"
                >
                  <div class="avatar me-1">
                    <?php if(session()->get("user_akses") == "admin") { ?>
                    <img src="<?= base_url("template")?>/assets/images/avatar/boy.png"/>
                    <?php }else{ ?>
                      <img src="<?= base_url('img/'.session()->get('foto'))?>"/>
                    <?php } ?>
                  </div>
                  <div class="d-none d-md-block d-lg-inline-block">
                    <?= session()->get("nama_dokter"); ?>
                  </div>
                </a>
                <div class="dropdown-menu dropdown-menu-end">                                  
                  <?php if(session()->get("user_akses") == "dokter") : ?>
                    <a class="dropdown-item" href="/edit_pwd/<?= session()->get("kode_dokter"); ?>"
                      ><i data-feather="edit"></i> Password </a
                    >
                  <?php endif; ?>
                  <div class="dropdown-divider"></div>
                  <a class="dropdown-item" href="<?= base_url('logout'); ?>"
                    ><i data-feather="log-out"></i> Logout</a
                  >
                </div>
              </li>
            </ul>
          </div>
        </nav>

        <div class="main-content container-fluid">
          <?= $this->renderSection('content') ?>          
        </div>

        <footer>
          <div class="footer clearfix mb-0 text-muted">
            <div class="float-start">
              <p>2022 &copy; Smart Pen and Medical Record</p>
            </div>
            <div class="float-end">
              <p>
                Crafted with
                <span class="text-danger"><i data-feather="heart"></i></span> by
                <a href="https://saugi.me">Smart Sistem</a>
              </p>
            </div>
          </div>
        </footer>
      </div>
    </div>
    <script src="<?= base_url("/template")?>/assets/js/feather-icons/feather.min.js"></script>
    <script src="<?= base_url("/template")?>/assets/vendors/perfect-scrollbar/perfect-scrollbar.min.js"></script>
    <script src="<?= base_url("/template")?>/assets/js/app.js"></script>

    <script src="<?= base_url("/template")?>/assets/vendors/chartjs/Chart.min.js"></script>
    <script src="<?= base_url("/template")?>/assets/vendors/apexcharts/apexcharts.min.js"></script>
    <script src="<?= base_url("/template")?>/assets/js/pages/dashboard.js"></script>

    <script src="<?= base_url("/template")?>/assets/js/main.js"></script>
    <?= $this->renderSection('js') ?>

  </body>
</html>
