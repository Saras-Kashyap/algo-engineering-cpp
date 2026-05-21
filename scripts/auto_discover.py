import os
import re
import json
import glob
import sys # Added this to allow the script to crash safely

def discover_problems():
    print("🔍 Scanning C++ files for metadata...")
    master_db = {"problems": []}
    seen_ids = set() # This acts as our security guard
    
    source_files = glob.glob('src/**/*.hpp', recursive=True)
    
    for file_path in source_files:
        category = os.path.basename(os.path.dirname(file_path))
        
        with open(file_path, 'r', encoding='utf-8') as f:
            content = f.read()
            id_match = re.search(r'\*\s*ID:\s*(\d+)', content)
            title_match = re.search(r'\*\s*Title:\s*(.+)', content)
            # ... (keep the rest of your regex matches here) ...
            
            if id_match and title_match:
                prob_id = int(id_match.group(1))
                
                # 🛑 THE SECURITY CHECK 🛑
                if prob_id in seen_ids:
                    print(f"❌ CRITICAL ERROR: Duplicate Problem ID {prob_id} found in {file_path}!")
                    print("❌ The build has been halted. Please remove the duplicate file.")
                    sys.exit(1) # This kills the script and fails the GitHub Action!
                
                seen_ids.add(prob_id) # Mark this ID as seen
                
                # ... (keep your existing master_db append logic here) ...