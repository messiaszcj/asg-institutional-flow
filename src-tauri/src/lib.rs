use std::process::Command;
#[cfg(target_os = "windows")]
use std::os::windows::process::CommandExt;
use tauri::Manager;

#[tauri::command]
fn get_snapshot(app: tauri::AppHandle, symbol: String) -> Result<String, String> {
    if !matches!(symbol.as_str(), "WIN" | "WDO" | "NQ" | "MNQ") {
        return Err("Ativo invalido".into());
    }
    let mut paths = Vec::new();
    if let Ok(resource) = app.path().resource_dir() {
        paths.push(resource.join("engine").join("asg_engine.exe"));
    }
    // During `tauri dev`, the engine lives next to the project.
    paths.push(std::path::PathBuf::from(env!("CARGO_MANIFEST_DIR")).join("..").join("engine").join("build").join("Release").join("asg_engine.exe"));
    let path = paths.into_iter().find(|p| p.is_file()).ok_or_else(||
        "Motor C++ nao encontrado. Execute scripts\\compilar_motor.bat".to_string())?;
    // Evita a janela de console piscando a cada atualizacao do snapshot.
    // CREATE_NO_WINDOW (0x08000000) aplica-se somente ao processo filho no Windows.
    let mut command = Command::new(path);
    command.arg(&symbol);
    #[cfg(target_os = "windows")]
    command.creation_flags(0x08000000);
    let output = command.output().map_err(|e| e.to_string())?;
    if !output.status.success() { return Err(String::from_utf8_lossy(&output.stderr).to_string()); }
    String::from_utf8(output.stdout).map_err(|e| e.to_string())
}

#[cfg_attr(mobile, tauri::mobile_entry_point)]
pub fn run() {
    tauri::Builder::default()
        .plugin(tauri_plugin_updater::Builder::new().build())
        .plugin(tauri_plugin_process::init())
        .invoke_handler(tauri::generate_handler![get_snapshot])
        .run(tauri::generate_context!())
        .expect("Erro ao iniciar ASG");
}
