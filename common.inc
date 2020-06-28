<?php

//定義ファイル
require_once dirname(__FILE__) . '/common_defs.inc';

//DB接続用
$dbh;

/**
 * DB接続
 */
function connect_db()
{
    global $dbh;
    try {
        $dbh = new PDO('mysql:host=mysql2011.db.sakura.ne.jp;dbname=studiok_315w', 'studiok', 'rintarou1974', 
            array(PDO::ATTR_EMULATE_PREPARES => false)
        );
        //エラー発生時に例外(PDOException)が発生するように設定
        $dbh->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
    } catch (PDOException $e) {
        log_to_file('データベース接続失敗。' . $e->getMessage());
    }
    return $dbh;
}

/**
 * クエリ発行
 */
function query($sql, $arr_bind = null)
{
    global $dbh;
    $sql = mb_convert_encoding($sql, DB_ENCODING, "UTF-8");
    $arr_bind_euc = [];
    //接続準備
    try {
        $sth = $dbh->prepare($sql);
    } catch (PDOException $e) {
        log_to_file("prepare error" . "\r\n"
            . mb_convert_encoding($sql, "UTF-8", DB_ENCODING) . "\r\n" . print_r($arr_bind, true) . "\r\n" . $e . "\r\n");
        exit;
    }
    //バインド処理
    if ($arr_bind) {
        try {
            foreach ($arr_bind as $key => $value) {
                $arr_bind_euc[$key] = mb_convert_encoding($value, DB_ENCODING, "UTF-8");
                //値がない場合はbindしない
                if ($value === null) {
                    continue;
                }
                $sth->bindValue($key, $arr_bind_euc[$key]);
            }
        } catch (PDOException $e) {
            log_to_file("bindValue error" . "\r\n"
                . mb_convert_encoding($sql, "UTF-8", DB_ENCODING) . "\r\n" . print_r($arr_bind, true) . "\r\n" . $e . "\r\n");
            exit;
        }
    }
    //実行
    try {
        $res = $sth->execute();
    } catch (PDOException $e) {
        log_to_file("execute error" . "\r\n"
            . mb_convert_encoding($sql, "UTF-8", DB_ENCODING) . "\r\n" . print_r($arr_bind, true) . "\r\n");
        exit;
    }
    //結果取得
    try {
        $result = $sth->fetchall(PDO::FETCH_ASSOC);
        $result = count($result) != 0 ? $result : null;
    } catch (PDOException $e) {
        log_to_file("fetch error" . "\r\n"
            . mb_convert_encoding($sql, "UTF-8", DB_ENCODING) . "\r\n" . print_r($arr_bind, true) . "\r\n");
        exit;
    }
    return $result;
}

/**
 * コミット
 */
function commit()
{
    global $conn;
    oci_commit($conn);
    return true;
}
/**
 * ロールバック
 */
function rollback()
{
    global $conn;
    oci_rollback($conn);
    return true;
}

/**
 * ログ出力
 */
function log_to_file($msg)
{
    if (!empty($msg)) {
		
		//ファイル名
        $filename = "log.txt";

		$str_file_path = "./" . $filename;
        $handle = fopen($str_file_path, 'a');
        list($micro, $Unixtime) = explode(' ', microtime());
        $time = date('Y/m/d H:i:s', $Unixtime) . '.' . round($micro * 1000);
        if (fwrite($handle, $time . "\r\n " . $msg . "\r\n") == false) {
            return false;
        }
        fclose($handle);
        return true;
    }
}
?>