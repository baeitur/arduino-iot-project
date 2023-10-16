<?php

namespace App\Controllers;

use App\Controllers\BaseController;

use function PHPSTORM_META\type;

class Download extends BaseController
{
    public function download($video=false)
    {
        return $this->response->download('./videos/'.$video, null);
    }

}
