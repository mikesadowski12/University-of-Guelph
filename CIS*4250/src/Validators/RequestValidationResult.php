<?php

namespace WellCat\Validators;

class RequestValidationResult
{
    private $success = false;
    private $validParameters = null;
    private $error = null;

    public function __construct($success, $validParameters = null, $error = null) {
        $this->success = $success;
        $this->validParameters = $validParameters;
        $this->error = $error;
    }

    public function GetError() {
        return $this->error;
    }

    public function GetParameter($paramName) {
        return $this->validParameters[$paramName];
    }

    public function GetParameters() {
        return $this->validParameters;
    }

    public function GetSuccess() {
        return $this->success;
    }

    public function HasParameter($paramName) {
        return array_key_exists($paramName, $this->validParameters);
    }
}
