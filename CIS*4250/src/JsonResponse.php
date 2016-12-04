<?php

namespace WellCat;

use Symfony\Component\HttpFoundation\Response;

class JsonResponse extends Response
{
    public function __construct($data = null, $http_code = 200)
    {
        if (is_null($data)) {
            $data = array(
                'success' => true
            );
        }
        $data = json_encode($data);
        return parent::__construct($data, $http_code, array(
            "content-type" => "application/json"
        ));
    }

    public static function missingParam(string $key)
    {
        $body = array(
            'success' => false,
            'error' => 'Missing '.$key
        );
        return new self($body, 404);
    }

    public static function userError(string $error)
    {
        $body = array(
            'success' => false,
            'error' => $error
        );
        return new self($body, 400);
    }

    public static function authError(string $error, $forbidden = false)
    {
        $code = $forbidden ? 401 : 403;
        $body = array (
            'success' => false,
            'error' => $error
        );
        return new self($body, $code);
    }

    public static function serverError()
    {
        $body = array(
            'success' => false,
            'error' => 'Unknown server error'
        );
        return new self($body, 500);
    }
}
