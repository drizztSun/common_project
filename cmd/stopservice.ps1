
Set-ExecutionPolicy RemoteSigned

$services = ('Akamai Device Posture', 'Akamai Osquery Daemon')

foreach ($serviceName in $services) {

    Write-Output ' stop {0} ' -f $serviceName 
    # Write-Verbose("stop service {0}"-f $serviceName)

    For ($i=0; $i -le 3; $i++) {

        if (Get-Service $serviceName -ErrorAction SilentlyContinue) {
            Stop-Service -Name $serviceName
            
            # Remove-Service -Name $serviceName
            # sc.exe delete $serviceName
        } else {
            Write-Verbose("service {0} has been removed"-f $serviceName)
            break
        }

        # net stop 'Akamai Device Posture'
        $target = Get-Service $serviceName -ErrorAction SilentlyContinue
        if (-not $target)
        {
            Write-Output "service " + $serviceName + " has been removed"
            break
        }
    }
} 