<?php

namespace WellCat\Services;

use Silex\Application;

class PetService
{
    protected $app;

    public function __construct(Application $app)
    {
        $this->app = $app;
    }

    /**
     * Function checks the ownership of a pet based on the current user
     * returns 3 if owner, 2 if writeable access, 1 if read only, and false if not accessable.
     * @param [int] $petID holds the id value of a pet.
     * @param [bool] $fitcat holds a true or false value based on if the search should be limited to fitcats or not.
     */
    public function CheckPetOwnership($petID, $fitcat)
    {
        $addition = ' ';
        if ($fitcat) {
            $addition = " AND p.fitcat = true";
        }

        $user = $this->app['session']->get('user');

        $sql = 'SELECT NULL FROM pet p WHERE p.petid = :petID AND p.ownerid = :userID'.$addition;
        $stmt = $this->app['db']->prepare($sql);
        $stmt->execute(array( 
            ':petID' => $petID,
            ':userID' => $user['userId']
        ));

        $result = $stmt->fetch(\PDO::FETCH_ASSOC);

        if ($result) {
            return 3;
        }
        else {
            $sql = 'SELECT a.access FROM accessibility a INNER JOIN pet p ON a.petid = p.petid WHERE a.petid = :petID AND a.userid = :userID'.$addition;
            $stmt = $this->app['db']->prepare($sql);
            $stmt->execute(array( 
                ':petID' => $petID,
                ':userID' => $user['userId']
            ));
            $result = $stmt->fetch(\PDO::FETCH_ASSOC);

            //if a result is found deal with it accordingly otherwise return 0;
            if ($result) {
                if($result['access'] == 'write') {
                    return 2;
                }
                else {
                    return 1;
                }
            }
            else {
                return 0;
            }
        }
    }

    public function GetAnimalTypeIDFromPet($petID)
    {
        if (!isset($petID) || !is_numeric($petID)) {
            throw new Exception('Invalid petID');
        }

        $sql = 'SELECT B.animaltypeid 
                FROM pet P
                    INNER JOIN breed B on B.breedid = P.breed
                WHERE P.petid = :petID';
        $stmt = $this->app['db']->prepare($sql);
        $stmt->execute(array(
            'petID' => $petID
        ));

        $result = $stmt->fetch(\PDO::FETCH_ASSOC);

        if ($result) {
            return (int)$result['animaltypeid'];
        }
        else {
            throw new Exception('Invalid petID');
        }
    }
}