<?php

namespace WellCat\Converters;

class StringToBooleanConverter implements ConverterInterface
{
    public static function Convert($value)
    {
        if (!is_string($value)) {
            throw new Exception('Invalid parameter value');
        }

        switch (strtolower($value)) {
            case 'true':
                return true;
            case 'false':
                return false;
            default:
                return null;
        }
    }
}