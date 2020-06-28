<?php
require_once dirname(__FILE__) . '/common.inc';
require_once dirname(__FILE__) . '/common_defs.inc';


//ご意見登録
function set_contact($data) {

    $str_sql = "
        insert into contact( 
            onamae
            , email
            , goiken
            , DELETE_FLG
        ) 
        values ( 
            :onamae
            , :email
            , :goiken
            , 0
        )
    ";

    //バインド
    $arr_binds = [];
    $arr_binds[':onamae']   = $data["onamae"];
    $arr_binds[':email']     = $data["email"];
    $arr_binds[':goiken']   = $data["goiken"];

    //SQLを実行
    $result = query($str_sql, $arr_binds);
    
    return true;
}


//データベース接続
if(!$dbh = connect_db()) {
	//DB接続失敗
	exit;
}


$eventId = null;

// イベントID取得
if (isset($_POST['eventId'])) {
	$eventId = $_POST['eventId'];
}

switch ($eventId) {
	case 'save':
        set_contact($_POST);
        $name = $_POST["onamae"];
        require('../view/thanks.php');
		break;

	default:
		break;
}

//データベースを閉じる
$dbh = null;