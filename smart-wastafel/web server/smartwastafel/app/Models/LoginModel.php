<?php

namespace App\Models;

use CodeIgniter\Database\MySQLi\Builder;
use CodeIgniter\Database\Query;
use CodeIgniter\Model;

class LoginModel extends Model
{

   protected $table = "users";
   protected $useTimestamps = true;
   protected $primaryKey = 'id';
   protected $allowedFields = [
       'name',
       'username',
       'password'
   ];

   protected $validationRules = [
      'username'  => 'required|min_length[3]',
      'password'  => 'required|min_length[8]',
   ];

   public function register($data = null)
   {
      $builder = $this->table('user_warga')
         ->insert($data);
      return $builder ? true : false;
   }

   public function cek_login($user)
   {
      $query = $this->table($this->table)
         ->where('username', $user)
         ->countAll();

      if ($query > 0) {
         $hasil = $this->table($this->table)
            ->where('username', $user)
            ->limit(1)
            ->get()
            ->getRowArray();
      } else {
         $hasil = array();
      }
      return $hasil;
   }

   public function getUsers()
	{
		$builder = $this->table($this->table)
			->orderBy($this->primaryKey, 'DESC');
		return $builder;
	}
}
