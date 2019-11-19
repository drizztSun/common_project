Set-ExecutionPolicy RemoteSigned
# Set-ExecutionPolicy Bypass
# Set-ExecutionPolicy Unrestricted  -Scope LocalMachine

$DpcExt = 'C:\ProgramData\osquery\akadp.ext.exe'
$Folder = 'C:\ProgramData\osquery'

if (Test-Path $DpcExt) {

    # stop dpclient.ext and osquery service
    $services = ('Akamai Device Posture', 'Akamai Osquery Daemon')

    foreach ($serviceName in $services) {

        Write-Output ' stop {0} ' -f $serviceName 
        # Write-Verbose("stop service {0}"-f $serviceName)

        For ($i=0; $i -le 3; $i++) {

            if (Get-Service $serviceName -ErrorAction SilentlyContinue) {
                Stop-Service -Name $serviceName

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

    # wait for service fully stopped
    Start-Sleep -s 10

    # clear the installation folder
    Remove-Item $Folder -Recurse;

    foreach ($serviceName in $services) {
        if (Get-Service $serviceName -ErrorAction SilentlyContinue) {
            sc.exe delete $serviceName
        }
    }
}

